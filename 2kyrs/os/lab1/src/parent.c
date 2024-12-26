#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_FILENAME 256
#define MAX_STRING 1024

int main() {
    int pipe1[2], pipe2[2];
    char filename1[MAX_FILENAME], filename2[MAX_FILENAME];
    ssize_t bytes_read;
    
    // Получаем имена файлов
    bytes_read = read(STDIN_FILENO, filename1, MAX_FILENAME);
    if (bytes_read <= 0) {
        write(STDERR_FILENO, "Error reading filename1\n", 23);
        exit(1);
    }
    filename1[strcspn(filename1, "\n")] = 0;
    
    bytes_read = read(STDIN_FILENO, filename2, MAX_FILENAME);
    if (bytes_read <= 0) {
        write(STDERR_FILENO, "Error reading filename2\n", 23);
        exit(1);
    }
    filename2[strcspn(filename2, "\n")] = 0;
    
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        write(STDERR_FILENO, "Pipe creation failed\n", 20);
        exit(1);
    }
    
    pid_t pid1 = fork();
    if (pid1 < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        exit(1);
    }
    
    if (pid1 == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        
        dup2(pipe1[0], STDIN_FILENO);
        
        char *args[] = {"./child1", filename1, NULL};
        execv(args[0], args);
        write(STDERR_FILENO, "Exec failed\n", 12);
        exit(1);
    }
    
    pid_t pid2 = fork();
    if (pid2 < 0) {
        write(STDERR_FILENO, "Fork failed\n", 12);
        exit(1);
    }
    
    if (pid2 == 0) {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        
        dup2(pipe2[0], STDIN_FILENO);
        
        char *args[] = {"./child2", filename2, NULL};
        execv(args[0], args);
        write(STDERR_FILENO, "Exec failed\n", 12);
        exit(1);
    }
    
    close(pipe1[0]);
    close(pipe2[0]);
    
    char input[MAX_STRING];
    while ((bytes_read = read(STDIN_FILENO, input, MAX_STRING)) > 0) {
        if (input[bytes_read-1] == '\n') {
            input[bytes_read-1] = '\0';
            bytes_read--;
        }
        
        if (bytes_read > 10) {
            write(pipe2[1], input, bytes_read + 1);
        } else {
            write(pipe1[1], input, bytes_read + 1);
        }
    }
    
    close(pipe1[1]);
    close(pipe2[1]);
    
    wait(NULL);
    wait(NULL);
    
    return 0;
}