#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void searchSubstringInFiles(const char *substring, int num_files, ...) {
    va_list files;
    va_start(files, num_files);

    for (int i = 0; i < num_files; i++) {
        const char *file_path = va_arg(files, const char *);
        FILE *file = fopen(file_path, "r");

        if (file == NULL) {
            perror("Ошибка открытия файла");
            continue;
        }

        printf("Файл: %s\n", file_path);
        
        char *line = NULL;
        size_t len = 0;
        size_t read;
        int line_number = 0;

        while ((read = getline(&line, &len, file)) != -1) {
            line_number++;
            char *current_pos = line;

            while (*current_pos != '\0') {
                char *search_pos = current_pos;
                const char *sub_pos = substring;

                while (*search_pos == *sub_pos && *sub_pos != '\0') {
                    search_pos++;
                    sub_pos++;
                }

                if (*sub_pos == '\0') {
                    printf("Найдено в строке %d, позиция %ld\n", line_number, current_pos - line + 1);
                }

                current_pos++;
            }
        }

        free(line);
        fclose(file);
    }

    va_end(files);
}

int main() {
    searchSubstringInFiles("AAASD", 2, "file1", "file2");
    return 0;
}