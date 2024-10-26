#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

    int char_to_value(char c) {
        if (c >= '0' && c <= '9')
            return c - '0';
        else if (c >= 'A' && c <= 'Z')
            return c - 'A' + 10;
        else if (c >= 'a' && c <= 'z')
            return c - 'a' + 10;
        else
            return -1;
    }

    char value_to_char(int val) {
        if (val >= 0 && val <= 9)
            return '0' + val;
        else if (val >= 10 && val <= 35)
            return 'A' + val - 10;
        else
            return '?';
    }

    char* add(const char* num1, const char* num2, int base) {
        int len1 = strlen(num1);
        int len2 = strlen(num2);
        int max_len = len1 > len2 ? len1 : len2;

        char* result = (char*)calloc(max_len + 2, sizeof(char));

        int carry = 0;
        int idx = 0;

        for (int i = 0; i < max_len; ++i) {
            int digit1 = (len1 - i - 1 >= 0 ? char_to_value(num1[len1 - i - 1]) : 0);
            int digit2 = (len2 - i - 1 >= 0 ? char_to_value(num2[len2 - i - 1]) : 0);

            if (digit1 == -1 || digit2 == -1 || digit1 >= base || digit2 >= base) {
                printf("Недопустимый символ в числе\n");
                free(result);
                return NULL;
            }

            int sum = digit1 + digit2 + carry;
            result[idx++] = value_to_char(sum % base);
            carry = sum / base;
        }

        if (carry > 0)
            result[idx++] = value_to_char(carry);


        for (int i = 0; i < idx / 2; ++i) {
            char temp = result[i];
            result[i] = result[idx - i - 1];
            result[idx - i - 1] = temp;
        }
        result[idx] = '\0';

        return result;
    }


    char* sum_numbers(int base, int count, ...) {
        if (base < 2 || base > 36) {
            printf("Основание системы счисления должно быть в диапазоне от 2 до 36\n");
            return NULL;
        }

        va_list args;
        va_start(args, count);

        char* total = (char*)malloc(2 * sizeof(char));
        strcpy(total, "0");
        for (int i = 0; i < count; ++i) {
            const char* num = va_arg(args, const char*);
            char* new_total = add(total, num, base);
            if (!new_total) {
                free(total);
                va_end(args);
                return NULL;
            }
            free(total);
            total = new_total;
        }

        va_end(args);
        return total;
    }

    int main() {
        char* result = sum_numbers(16, 5, "A1", "FF", "1B3", "0", "F");
        if (result) {
            printf("Результат: %s\n", result);
            free(result);
        }

        return 0;
    }