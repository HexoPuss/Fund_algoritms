#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_STRING 1024

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
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
    if (argc != 2) {
        write(STDERR_FILENO, "Usage error\n", 11);
        exit(1);
    }
    
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        write(STDERR_FILENO, "File opening failed\n", 19);
        exit(1);
    }
    
    char buffer[MAX_STRING];
    ssize_t bytes_read;
    
    while ((bytes_read = read(STDIN_FILENO, buffer, MAX_STRING)) > 0) {
        remove_vowels(buffer);
        write(STDOUT_FILENO, buffer, strlen(buffer));
        write(STDOUT_FILENO, "\n", 1);
        write(fd, buffer, strlen(buffer));
        write(fd, "\n", 1);
    }
    
    close(fd);
    return 0;
}