#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2], pipe2[2];
    char filename1[BUFFER_SIZE], filename2[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    
    read(STDIN_FILENO, filename1, BUFFER_SIZE);
    filename1[strcspn(filename1, "\n")] = 0;
    read(STDIN_FILENO, filename2, BUFFER_SIZE);
    filename2[strcspn(filename2, "\n")] = 0;

    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        close(pipe1[1]);
        char *args[] = {"./child", filename1, NULL};
        dup2(pipe1[0], STDIN_FILENO);
        execv(args[0], args);
        exit(1);
    }

    if (fork() == 0) {
        close(pipe2[1]);
        char *args[] = {"./child", filename2, NULL};
        dup2(pipe2[0], STDIN_FILENO);
        execv(args[0], args);
        exit(1);
    }

    close(pipe1[0]);
    close(pipe2[0]);

    while (1) {
        ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) break;
        
        // Новое правило фильтрации по длине строки
        size_t len = strcspn(buffer, "\n");
        if (len > 10) {
            write(pipe1[1], buffer, bytes_read);
        } else {
            write(pipe2[1], buffer, bytes_read);
        }
    }

    close(pipe1[1]);
    close(pipe2[1]);
    
    wait(NULL);
    wait(NULL);
    
    return 0;
}