#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void exclude_digits(FILE* in, FILE* out) {
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, out);
        }
    }
}

void count_latin_letters(FILE* in, FILE* out) {
    char line[1024];
    while (fgets(line, sizeof(line), in) != NULL) {
        int count = 0;
        for (int i = 0; line[i] != '0'; i++) {
            if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) {
                count++;
            }
        }
        fprintf(out, "%d\n", count);
    }
}

void count_special_symbols(FILE* in, FILE* out) {
    char line[1024];
    while (fgets(line, sizeof(line), in) != NULL) {
        int count = 0;
        for (int i = 0; line[i] != '0'; i++) {
            if (!isdigit(line[i]) && !isalpha(line[i]) && !isspace(line[i])) {
                count++;
            }
        }
        fprintf(out, "%d\n", count);
    }
}

void replace_non_digits(FILE* in, FILE* out) {
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (!isdigit(ch)) {
            fprintf(out, "%X", ch);
        } else {
            fputc(ch, out);
        }
    }
}

int is_flag(char* input, char* flag){
    
    char comp1[3];
    char comp2[3];
    char comp3[3];
    char comp4[3];
    
    strcpy(comp1, "-n");
    strcat(comp1, flag);
    
    strcpy(comp2, "-");
    strcat(comp2, flag);
    
    strcpy(comp3, "/n");
    strcat(comp3, flag);
    
    strcpy(comp4, "/");
    strcat(comp4, flag);
    
    
    if (strcmp(input, comp1) == 0 || strcmp(input, comp2) == 0 || strcmp(input, comp3) == 0 || strcmp(input, comp4) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s [-flag] input_file [output_file]\n", argv[0]);
        return 1;
    }

    char* flag = argv[1];
    char* input_file = argv[2];
    char output_file[256];

    if (argc == 4 && (strstr(argv[1], "n"))) {
        // Пользователь указал имя выходного файла
        strncpy(output_file, argv[3], sizeof(output_file));
        output_file[sizeof(output_file) - 1] = '\0'; // Гарантируем завершение строки
    } else if(argc == 3) {
        // Используем префикс "out_" по умолчанию
        strcpy(output_file, "out_");

        // Предполагаем, что имя входного файла находится в argv[2]
        char* input_file = argv[2];

        // Находим позицию последней точки в имени входного файла
        char* dot_pos = strrchr(input_file, '.');
        if (dot_pos != NULL) {
            // Вычисляем длину имени без расширения
            size_t prefix_length = dot_pos - input_file;
            // Добавляем часть имени входного файла к "out_"
            strncat(output_file, input_file, prefix_length);
        } else {
            // Добавляем полное имя входного файла к "out_"
            strcat(output_file, input_file);
        }
    }
    


    FILE* in = fopen(input_file, "r");
    if (!in) {
        perror("Error opening input file");
        return 1;
    }

    FILE* out = fopen(output_file, "w");
    if (!out) {
        perror("Error opening output file");
        fclose(in);
        return 1;
    }

    if (is_flag(flag, "d")) {
        exclude_digits(in, out);
    } else if (is_flag(flag, "i")) {
        count_latin_letters(in, out);
    } else if (is_flag(flag, "s")) {
        count_special_symbols(in, out);
    } else if (is_flag(flag, "a")) {
        replace_non_digits(in, out);
    } else {
        fprintf(stderr, "Unknown flag: %s\n", flag);
        fclose(in);
        fclose(out);
        return 1;
    }

    fclose(in);
    fclose(out);
    return 0;
}
