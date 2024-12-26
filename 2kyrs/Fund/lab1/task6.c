#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int my_atof(const char *str, long double* num) {
    long double result = 0.0;
    long double fraction = 0.0;
    long double divisor = 10.0;
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

    if(*str != '\0'){
        return 1;
    }

    result += fraction;
    result *= sign;
    *num = result;
    return 0;
}


long double Calculation(long double func(), long double eps, long double intStart, long double intEnd){
    long double i, res;
    res = 0;
    for(i = intStart; i < intEnd; i += eps){
        res += func(i) * eps;
    }
    return res;
}


long double integral_a(long double x) {
    if(x == 0){
        return 0;
    }
    return log(1 + x) / x;
}

long double integral_b(long double x) {
    return exp(-x * x / 2);
}

long double integral_c(long double x) {
    return log(1 / (1 - x));
}

long double integral_d(long double x) {
    return pow(x, x);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование:./t6 {epsilon}\n");
        return 1;
    }

    long double eps;
    if (my_atof(argv[1], &eps)) {
        fprintf(stderr, "Ошибка: '%s' не является допустимым вещественным числом.\n", argv[1]);
        return 2;
    }

    printf("eps - %Lf\n", eps);
    printf("a - %Lf\n", Calculation(integral_a, eps, 0, 1));
    printf("b - %Lf\n", Calculation(integral_b, eps, 0, 1));
    printf("c - %Lf\n", Calculation(integral_c, eps, 0, 1));
    printf("d - %Lf\n", Calculation(integral_d, eps, 0, 1));

    return 0;
}