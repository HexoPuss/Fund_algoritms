#include <stdio.h>
#include <ctype.h>

// Функция для преобразования символа в его числовое значение
int char_to_value(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    else
        return -1; // Недопустимый символ
}

// Функция проверки строки на соответствие системе счисления
int is_valid_number(const char* number, int base) {
    if (base < 2 || base > 36) {
        fprintf(stderr, "Основание системы счисления должно быть между 2 и 36.\n");
        return 0;
    }

    if (number == NULL || *number == '\0') {
        fprintf(stderr, "Пустая строка не является допустимым числом.\n");
        return 0;
    }

    // Если число начинается с '-', пропускаем его
    int start = 0;
    if (number[0] == '-') {
        start = 1;
        if (number[1] == '\0') { // Строка состоит только из '-'
            fprintf(stderr, "Недопустимый формат числа.\n");
            return 0;
        }
    }

    for (int i = start; number[i] != '\0'; i++) {
        int value = char_to_value(number[i]);
        if (value == -1 || value >= base) {
            // Символ не является допустимым в данной системе счисления
            return 0;
        }
    }

    return 1; // Число соответствует системе счисления
}

int main() {
    // Примеры использования функции
    const char* num1 = "1A3F";
    int base1 = 16;

    const char* num2 = "123G";
    int base2 = 16;

    if (is_valid_number(num1, base1)) {
        printf("Число %s допустимо в системе счисления с основанием %d.\n", num1, base1);
    } else {
        printf("Число %s недопустимо в системе счисления с основанием %d.\n", num1, base1);
    }

    if (is_valid_number(num2, base2)) {
        printf("Число %s допустимо в системе счисления с основанием %d.\n", num2, base2);
    } else {
        printf("Число %s недопустимо в системе счисления с основанием %d.\n", num2, base2);
    }

    return 0;
}