#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Функция для чтения следующего слова из файла
int readWord(FILE *file, char *buffer) {
    int c;
    int i = 0;
    
    // Пропускаем пробельные символы
    while ((c = fgetc(file)) != EOF && isspace(c));

    if (c == EOF) {
        return 0; // Слов больше нет
    }

    // Читаем слово
    do {
        buffer[i++] = c;
        c = fgetc(file);
    } while (c != EOF && !isspace(c) && i < BUFFER_SIZE - 1);

    buffer[i] = '\0';

    // Если слово слишком длинное, пропускаем оставшиеся символы этого слова
    while (c != EOF && !isspace(c)) {
        c = fgetc(file);
    }

    return 1; // Слово успешно прочитано
}

// Функция для объединения файлов
int mergeFiles(const char* file1, const char* file2, const char* outputFile) {
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

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Неверное количество аргументов.\n");
        fprintf(stderr, "Использование: %s -r файл1 файл2 файл_выхода\n", argv[0]);
        return 1;
    }
    int outcome;

    if (strcmp(argv[1], "-r") == 0 && strcmp(argv[1], "/r") == 0) {
        outcome = mergeFiles(argv[2], argv[3], argv[4]);
    }else{
        fprintf(stderr, "Неверный флаг.\n");
        return 1;
    }
    if(outcome == 2){
        fprintf(stderr, "Ошибка открытия файла.\n");
    }
    return outcome;
}