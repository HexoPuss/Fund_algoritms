#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_STRING 1024
#define SHM_SIZE MAX_STRING

int is_vowel(char c) {
    c = tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

void remove_vowels(char *str) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (!is_vowel(str[i])) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        write(STDERR_FILENO, "Usage error\n", 12);
        exit(1);
    }

    char *filename = argv[1];
    const char *shm_name = argv[2];
    const char *sem_empty_name = argv[3];
    const char *sem_full_name = argv[4];

    // Открытие общей памяти
    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        write(STDERR_FILENO, "Shared memory opening failed\n", 29);
        exit(1);
    }

    // Отображение общей памяти в адресное пространство
    char *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        write(STDERR_FILENO, "Memory mapping failed\n", 22);
        exit(1);
    }

    // Открытие семафоров
    sem_t *sem_empty = sem_open(sem_empty_name, 0);
    sem_t *sem_full = sem_open(sem_full_name, 0);
    if (sem_empty == SEM_FAILED || sem_full == SEM_FAILED) {
        write(STDERR_FILENO, "Semaphore opening failed\n", 25);
        exit(1);
    }

    // Открытие файла на запись
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        write(STDERR_FILENO, "File opening failed\n", 20);
        exit(1);
    }

    char buffer[MAX_STRING];

    while (1) {
        // Ожидание данных от родительского процесса
        sem_wait(sem_full);

        // Чтение данных из общей памяти
        strcpy(buffer, shm_ptr);

        // Сигнализировать, что память пуста
        sem_post(sem_empty);

        // Проверка на сигнал завершения
        if (buffer[0] == '\0') {
            break;
        }

        remove_vowels(buffer);

        size_t len = strlen(buffer);

        write(STDOUT_FILENO, buffer, len);
        write(STDOUT_FILENO, "\n", 1);
        write(fd, buffer, len);
        write(fd, "\n", 1);
    }

    // Очистка ресурсов
    munmap(shm_ptr, SHM_SIZE);
    close(shm_fd);
    sem_close(sem_empty);
    sem_close(sem_full);
    close(fd);

    return 0;
}