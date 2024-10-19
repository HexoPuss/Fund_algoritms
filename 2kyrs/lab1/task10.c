#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LENGTH 100


int isValidNumber(const char *numStr, int base) {
    int len = strlen(numStr);
    int start = 0;
    // Skip sign if present
    if (numStr[0] == '-' || numStr[0] == '+')
        start = 1;

    for (int i = start; i < len; i++) {
        char digit = toupper(numStr[i]);
        int digitVal;

        if (isdigit(digit))
            digitVal = digit - '0';
        else if (isalpha(digit))
            digitVal = digit - 'A' + 10;
        else
            return 0; // Invalid character

        if (digitVal >= base)
            return 0; // Digit not valid for the base
    }
    return 1;
}


long long int toDecimal(const char *numStr, int base) {
    long long int num = 0;
    int len = strlen(numStr);
    int sign = 1;
    int start = 0;

    // Check for sign
    if (numStr[0] == '-') {
        sign = -1;
        start = 1;
    } else if (numStr[0] == '+') {
        start = 1;
    }

    for (int i = start; i < len; i++) {
        char digit = toupper(numStr[i]);
        int digitVal;

        if (isdigit(digit))
            digitVal = digit - '0';
        else
            digitVal = digit - 'A' + 10;

        num = num * base + digitVal;
    }
    return sign * num;
}


void fromDecimal(long long int num, int base, char *buffer) {
    char temp[MAX_LENGTH];
    int index = 0;
    int isNegative = 0;

    if (num == 0) {
        strcpy(buffer, "0");
        return;
    }

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num > 0) {
        int rem = num % base;
        if (rem < 10)
            temp[index++] = rem + '0';
        else
            temp[index++] = (rem - 10) + 'A';
        num /= base;
    }

    if (isNegative)
        temp[index++] = '-';

    temp[index] = '\0';


    for (int i = 0; i < index; i++) {
        buffer[i] = temp[index - i - 1];
    }
    buffer[index] = '\0';
}

int main() {
    int base;
    char numStr[MAX_LENGTH];
    long long int maxNum = 0;
    int firstNum = 1; // Flag to handle the first number input

    printf("Введите основание системы счисления (2..36): ");
    scanf("%d", &base);
    getchar();

    if (base < 2 || base > 36) {
        printf("Некорректное основание\n");
        return 1;
    }

    printf("Введите числа (введите 'Stop' для завершения):\n");
    while (1) {
        fgets(numStr, MAX_LENGTH, stdin);
        numStr[strcspn(numStr, "\n")] = '\0';

        if (strcmp(numStr, "Stop") == 0)
            break;

        if (!isValidNumber(numStr, base)) {
            printf("Некорректное число: %s\n", numStr);
            continue;
        }

        long long int currentNum = toDecimal(numStr, base);
        if (firstNum || llabs(currentNum) > llabs(maxNum)) {
            maxNum = currentNum;
            firstNum = 0;
        }
    }

    if (firstNum) {
        printf("Не было введено ни одного корректного числа.\n");
        return 0;
    }

    printf("Максимальное по модулю: %lld\n", maxNum);

    char buffer[MAX_LENGTH];
    int newBases[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        fromDecimal(maxNum, newBases[i], buffer);
        
        int idx = 0;
        while (buffer[idx] == '0' && buffer[idx + 1] != '\0') {
            idx++;
        }
        printf("Представление в системе с основанием %d: %s\n", newBases[i], buffer + idx);
    }

    return 0;
}