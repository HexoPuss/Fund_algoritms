#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILENAME 256
#define MAX_STRING 1024
#define SHM_SIZE MAX_STRING

int main() {
    char filename1[MAX_FILENAME], filename2[MAX_FILENAME];

    // Чтение имени файла 1 из стандартного ввода
    ssize_t bytes_read = read(STDIN_FILENO, filename1, MAX_FILENAME);
    if (bytes_read <= 0) {
        write(STDERR_FILENO, "Error reading filename1\n", 23);
        exit(1);
    }
    filename1[strcspn(filename1, "\n")] = '\0';

    // Чтение имени файла 2 из стандартного ввода
    bytes_read = read(STDIN_FILENO, filename2, MAX_FILENAME);
    if (bytes_read <= 0) {
        write(STDERR_FILENO, "Error reading filename2\n", 23);
        exit(1);
    }
    filename2[strcspn(filename2, "\n")] = '\0';

    // Создание объектов общей памяти
    char *shm_name1 = "/shm_child1";
    char *shm_name2 = "/shm_child2";

    int shm_fd1 = shm_open(shm_name1, O_CREAT | O_RDWR, 0666);
    int shm_fd2 = shm_open(shm_name2, O_CREAT | O_RDWR, 0666);

    if (shm_fd1 == -1 || shm_fd2 == -1) {
        write(STDERR_FILENO, "Shared memory creation failed\n", 30);
        exit(1);
    }

    // Установка размера общей памяти
    ftruncate(shm_fd1, SHM_SIZE);
    ftruncate(shm_fd2, SHM_SIZE);

    // Отображение общей памяти в адресное пространство процесса
    char *shm_ptr1 = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd1, 0);
    char *shm_ptr2 = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);

    if (shm_ptr1 == MAP_FAILED || shm_ptr2 == MAP_FAILED) {
        write(STDERR_FILENO, "Memory mapping failed\n", 22);
        exit(1);
    }

    // Создание семафоров для синхронизации
    sem_t *sem_empty1 = sem_open("/sem_empty1", O_CREAT, 0666, 1); // Память пуста
    sem_t *sem_full1 = sem_open("/sem_full1", O_CREAT, 0666, 0);   // Память полна

    sem_t *sem_empty2 = sem_open("/sem_empty2", O_CREAT, 0666, 1);
    sem_t *sem_full2 = sem_open("/sem_full2", O_CREAT, 0666, 0);

    if (sem_empty1 == SEM_FAILED || sem_full1 == SEM_FAILED ||
        sem_empty2 == SEM_FAILED || sem_full2 == SEM_FAILED) {
        write(STDERR_FILENO, "Semaphore creation failed\n", 26);
        exit(1);
    }

    // Создание первого дочернего процесса
    pid_t pid1 = fork();
    if (pid1 < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        exit(1);
    }
    if (pid1 == 0) {
        // Дочерний процесс 1
        // Закрытие неиспользуемой общей памяти и семафоров
        munmap(shm_ptr2, SHM_SIZE);
        close(shm_fd2);
        sem_close(sem_empty2);
        sem_close(sem_full2);

        char *args[] = {"./child", filename1, shm_name1, "/sem_empty1", "/sem_full1", NULL};
        execv(args[0], args);
        write(STDERR_FILENO, "Exec failed\n", 12);
        exit(1);
    }

    // Создание второго дочернего процесса
    pid_t pid2 = fork();
    if (pid2 < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        exit(1);
    }
    if (pid2 == 0) {
        // Дочерний процесс 2
        // Закрытие неиспользуемой общей памяти и семафоров
        munmap(shm_ptr1, SHM_SIZE);
        close(shm_fd1);
        sem_close(sem_empty1);
        sem_close(sem_full1);

        char *args[] = {"./child", filename2, shm_name2, "/sem_empty2", "/sem_full2", NULL};
        execv(args[0], args);
        write(STDERR_FILENO, "Exec failed\n", 12);
        exit(1);
    }

    // Родительский процесс
    // Чтение ввода и запись в общую память
    char input[MAX_STRING];
    while ((bytes_read = read(STDIN_FILENO, input, MAX_STRING)) > 0) {
        // Удаление символа новой строки
        if (input[bytes_read - 1] == '\n') {
            input[bytes_read - 1] = '\0';
            bytes_read--;
        }

        size_t len = bytes_read;

        if (len > 10) {
            // Запись в общую память для дочернего процесса 2
            sem_wait(sem_empty2);
            memcpy(shm_ptr2, input, len + 1);
            sem_post(sem_full2);
        } else {
            // Запись в общую память для дочернего процесса 1
            sem_wait(sem_empty1);
            memcpy(shm_ptr1, input, len + 1);
            sem_post(sem_full1);
        }
    }

    // Отправка сигнала о завершении
    sem_wait(sem_empty1);
    shm_ptr1[0] = '\0';
    sem_post(sem_full1);

    sem_wait(sem_empty2);
    shm_ptr2[0] = '\0';
    sem_post(sem_full2);

    // Ожидание завершения дочерних процессов
    wait(NULL);
    wait(NULL);

    // Очистка ресурсов
    munmap(shm_ptr1, SHM_SIZE);
    munmap(shm_ptr2, SHM_SIZE);
    close(shm_fd1);
    close(shm_fd2);
    shm_unlink(shm_name1);
    shm_unlink(shm_name2);

    sem_close(sem_empty1);
    sem_close(sem_full1);
    sem_close(sem_empty2);
    sem_close(sem_full2);
    sem_unlink("/sem_empty1");
    sem_unlink("/sem_full1");
    sem_unlink("/sem_empty2");
    sem_unlink("/sem_full2");

    return 0;
}