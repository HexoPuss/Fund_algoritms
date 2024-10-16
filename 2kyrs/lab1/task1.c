#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int my_atoi(const char *str, int* num) {
    int result = 0;
    int sign = 1;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (1) {
        if(isdigit(*str)){
            int digit = *str - '0';

            result = result * 10 + digit;
            str++;
        }else if(*str != '\0'){
            return 1;
        }else{
            break;
        }
    }

    *num = sign * result;
    return 0;
}


double my_atof(const char *str) {
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 10.0;
    int sign = 1;
    int has_decimal = 0;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Обработка целой и дробной части
    while (isdigit(*str) || (*str == '.' && !has_decimal)) {
        if (*str == '.') {
            has_decimal = 1;
            str++;
            continue;
        }


        if (!has_decimal) {
            result = result * 10.0 + (*str - '0');
        } else {
            fraction += (*str - '0') / divisor;
            divisor *= 10.0;
        }
        str++;
    }

    result += fraction;
    result *= sign;

    return result;
}


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

int caseH(int x){
    if(x > 100 || x == 0){
        printf("кратных чисел в пределах 100 нет\n");
    }
    for(int i = x; i <= 100; i += x){
        printf("число %d делится на %d\n", i, x);
    }
}

int caseP(int x){
    if(x < 0){
        return 0;
    }

    if(x == 0){
        return -1;
    }

    for(int i = 2; i < x / 2; i++){
        if(x % i == 0){
            return 0;
            break;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    // Проверяем, что передано минимум 2 аргумента (программа + минимум 1 параметр)
    if (argc != 3) {
        fprintf(stderr , "некорректное число аргументов");
        return 1;
    }

    int x = 0;
    char flag = '\0';

    for (int i = 1; i < argc; i++) {
        if(my_atoi(argv[i][0], &x)){
            if(strlen(argv[i]) == 2){
                flag = argv[1];
            }else{
                printf("неверная длинна флага");
            }
        }
    }

    if (flag == '\0') {
        fprintf(stderr,"Флаг не был указан.n");
    }

    int result;

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
            result = caseP(x);
            if(result == 1){
                printf("простое\n");
            } else if(result == 0){
                printf("составное\n");
            } else{
                print("это нуль");
            }
            break;
        case 's':
            if(x == 0){
                printf("0\n");
                break;
            }
            if(x < 0){
                printf("-");
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
            printf("сумма натуральных чисел от 1 да %d - %d\n", x, nsum);
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
