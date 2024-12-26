#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024


int readWord(FILE *file, char *buffer) {
    int c;
    int i = 0;
    
    
    while ((c = fgetc(file)) != EOF && isspace(c));

    if (c == EOF) {
        return 0;
    }


    do {
        buffer[i++] = c;
        c = fgetc(file);
    } while (c != EOF && !isspace(c) && i < BUFFER_SIZE - 1);

    buffer[i] = '\0';

    // Если слово слишком длинное, пропускаем оставшиеся символы этого слова
    while (c != EOF && !isspace(c)) {
        c = fgetc(file);
    }

    return 1; 
}


int rFlag(const char* file1, const char* file2, const char* outputFile) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(outputFile, "w");

    if (!f1 || !f2 || !out) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (out) fclose(out);
        return 2;
    }

    char word1[BUFFER_SIZE];
    char word2[BUFFER_SIZE];
    int hasWord1 = 0, hasWord2 = 0;

    // Читаем начальные слова из каждого файла
    hasWord1 = readWord(f1, word1);
    hasWord2 = readWord(f2, word2);

    // Поочередно записываем слова из файлов в выходной файл
    while (hasWord1 || hasWord2) {
        if (hasWord1) {
            fprintf(out, "%s ", word1);
            hasWord1 = readWord(f1, word1);
        }
        if (hasWord2) {
            fprintf(out, "%s ", word2);
            hasWord2 = readWord(f2, word2);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(out);

    return 0;
}

void convert_to_lower(char *lexeme) {
    for (int i = 0; lexeme[i]; i++) {
        if (isalpha(lexeme[i])) {
            lexeme[i] = tolower(lexeme[i]);
        }
    }
}

void convert_to_base4(char *output, char *lexeme) {
    char buffer[50];
    output[0] = '0';

    for (int i = 0; lexeme[i]; i++) {
        int value = (int)lexeme[i];
        int j = 0;

        while (value > 0) {
            buffer[j++] = (value % 4) + '0';
            value /= 4;
        }

        while (j > 0) {
            strncat(output, &buffer[--j], 1);
        }
        strcat(output, " ");
    }
}

void convert_to_base8(char *output, char *lexeme) {
    char buffer[50];
    output[0] = '0';

    for (int i = 0; lexeme[i]; i++) {
        snprintf(buffer, sizeof(buffer), "%o", lexeme[i]);
        strcat(output, buffer);
        strcat(output, " ");
    }
}

int aFlag(const char *file, const char *file_out) {
    FILE *f = fopen(file, "r");
    if (!f) {
        perror("Failed to open input file");
        fclose(f);
        return 1;
    }

    FILE *fout = fopen(file_out, "w");
    if (!fout) {
        perror("Failed to open output file\n");
        fclose(fout);
        return 1;
    }

    char line[1024];
    int lexeme_count = 0;

    while (fgets(line, sizeof(line), f)) {
        char *lexeme = strtok(line, " \t\n");
        while (lexeme) {
            lexeme_count++;

            if (lexeme_count % 10 == 0) {
                char temp[1024];
                convert_to_lower(lexeme);
                convert_to_base4(temp, lexeme);
                fprintf(fout, "%s", temp);
            } else if (lexeme_count % 2 == 0 && lexeme_count % 10 != 0) {
                convert_to_lower(lexeme);
                fprintf(fout, "%s ", lexeme);
            } else if (lexeme_count % 5 == 0 && lexeme_count % 10 != 0) {
                char temp[1024];
                convert_to_base8(temp, lexeme);
                fprintf(fout, "%s", temp);
            } else {
                fprintf(fout, "%s ", lexeme);
            }

            lexeme = strtok(NULL, " \t\n");
        }
    }

    fclose(f);
    fclose(fout);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Неверное количество аргументов.\n");
        return 1;
    }
    int outcome;

    if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "/r") == 0) {
        if(argc != 5){
            fprintf(stderr, "Неверное количество аргументов.\n");
            return 2;
        }
        outcome = rFlag(argv[2], argv[3], argv[4]);
    }if(strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a") == 0){
        if(argc != 4){
            fprintf(stderr, "Неверное количество аргументов.\n");
            return 2;
        }
        outcome = aFlag(argv[2], argv[3]);
    }else{
        fprintf(stderr, "Неверный флаг .\n");
        return 1;
    }
    if(outcome != 0){
        fprintf(stderr, "Ошибка открытия файла.\n");
    }
    return outcome;
}