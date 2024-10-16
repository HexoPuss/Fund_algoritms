#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



char digitToHexChar(int digit) {
    if (digit < 10)
        return '0' + digit;
    else
        return 'A' + (digit - 10);
}

int is_number(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (!*str) return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int intpow(int x, int y){
    if(y == 0){
        return 1;
    }
    int tmp = x;
    while(y > 1){
        x *= tmp;
        y--;
    }
    return x;
}

int main(int argc, char *argv[]) {
    // Проверяем, что передано минимум 2 аргумента (программа + минимум 1 параметр)
    if (argc != 3) {
        fprintf(stderr , "некорректное число флагов");
        return 1;
    }

    int x = 0;
    char flag = '0';

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' || argv[i][0] == '/') {
            if (strlen(argv[i]) > 1) {
                flag = argv[i][1];
            } else {
                fprintf(stderr ,"Некорректный флаг: %sn", argv[i]);
                return 1;
            }
        }
        else if (is_number(argv[i])) {
            x = atoi(argv[i]);
        }
        else {
            fprintf(stderr,"Неизвестный аргумент: %sn", argv[i]);
            return 1;
        }
    }

    if (flag == '0') {
        fprintf(stderr,"Флаг не был указан.n");
    }

    switch (flag) {
        case 'h':
            if(x < 0){
                x = -x;
            }

            if(x > 100 || x == 0){
                printf("кратных чисел в пределах 100 нет\n");
                break;
            }

            for(int i = x; i <= 100; i += x){
                printf("число %d делится на %d\n", i, x);
            }
            break;
        case 'p':
            if(x < 0){
                x = -x;
            }
            int breaking = 0;
            if(x == 0){
                printf("это же нуль!\n");
            }

            for(int i = 2; i < x / 2; i++){
                if(x % i == 0){
                    printf("число x - составное\n");
                    breaking = 1;
                    break;
                }
            }

            if(breaking){
                break;
            }

            printf("число x - простое\n");

            break;
        case 's':
            if(x == 0){
                printf("0\n");
                break;
            }
            if(x < 0){
                x = -x;
            }

            int temp = x;
            int power = 1;

            while (temp >= 16) {
                temp /= 16;
                power *= 16;
            }

            int started = 0;

            while (power > 0) {
                int digit = (x / power) % 16;

                if (!started) {
                    if (digit != 0) {
                        printf("%c", digitToHexChar(digit));
                        started = 1;
                    }
                } else {
                    printf(" %c", digitToHexChar(digit));
                }
                power /= 16;
            }
            printf("\n");
            
            break;
        case 'e':
            if(x > 10){
                printf("x должен быть не мольше 10!\n");
                break;
            }

            for (int i = 2; i <= 10; i++){
                for(int j = 1; j <= x; j++){
                    printf(" %d", intpow(i, j));
                }
                printf("\n");
            }
            break;
        case 'a':
            if(x < 0){
                x = -x;
            }
            int nsum = 0;

            for(int i = 0; i < x; i++){
                nsum += i;
            }
            printf("сумма натуральных чискл от 1 да %d - %d\n", x, nsum);
            break;
        case 'f':
            if(x < 0){
                x = -x;
            }
            int fact = 1;
            for(int i = 1; i <= x; i++){
                fact *= i;
            }
            printf("факториал %d - %d\n", x, fact);
            break;
        default:
            fprintf(stderr, "Неизвестный флаг: %c\n", flag);
            return 2;
    }

    return 0;
}
