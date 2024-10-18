#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

int my_atof(const char *str, double* num) {
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

int compareFloats(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

int solveQuadratic(double a, double b, double c, double epsilon, double* result) {
    double discriminant = b*b - 4*a*c;
    if (compareFloats(discriminant, 0, epsilon)) {
        result[0] = -b / (2*a);
        return 1;
    } else if (discriminant > 0) {
        result[0] = (-b + sqrt(discriminant)) / (2*a);
        result[1] = (-b - sqrt(discriminant)) / (2*a);
        return 2;
    } else {
        return 0;
    }
}

int checkMultiple(int a, int b) {
    if (b != 0 && a % b == 0) {
        return 1;
    } else {
        return 0;
    }
}

int checkTriangle(double a, double b, double c, double epsilon) {
    if (compareFloats(a*a + b*b, c*c, epsilon) ||
        compareFloats(a*a + c*c, b*b, epsilon) ||
        compareFloats(b*b + c*c, a*a, epsilon)) {
        return 1;
    } else {
        return 0;
    }
}

void permutations(double a, double b, double c, int* perm){
    perm[0] = 123;
    perm[1] = 132;
    perm[2] = 213;
    perm[3] = 231;
    perm[4] = 312;
    perm[5] = 321;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./t3 flag [parameters]\n");
        return 1;
    }

    if (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "/q") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Error: -q flag requires 4 parameters\n");
            return 1;
        }
        double vars[3];
        double a, b, c, epsilon;
        if(my_atof(argv[2], &epsilon)){
            printf("invalid number 2");
            return 2;
        }
        if(my_atof(argv[3], &b)){
            printf("invalid number 3");
            return 2;
        }
        if(my_atof(argv[4], &c)){
            printf("invalid number 4");
            return 2;
        }
        if(my_atof(argv[5], &a)){
            printf("invalid number 5");
            return 2;
        }
        
        vars[0] = a;
        vars[1] = b;
        vars[2] = c;
        int perm[6];
        double result[2];
        int outcome;
        permutations(a, b, c, perm);
        for(int i = 0; i < 6; i++){
            printf("for %lfx^2 + %lfx + %lf: ", vars[(perm[i] / 100) - 1], vars[((perm[i] % 100) / 10) - 1], vars[(perm[i] % 10) - 1]);
            outcome = solveQuadratic(vars[(perm[i] / 100) - 1], vars[((perm[i] % 100) / 10) - 1], vars[(perm[i] % 10) - 1], epsilon, result);
            if(outcome == 0){
                printf("no real roots\n");
            }else if(outcome == 1){
                printf("one root - %lf\n", result[0]);
            }else{
                printf("two roots - %lf, %lf\n", result[0], result[1]);
            }

        }
        
    } else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "/m") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: -m flag requires 2 parameters\n");
            return 1;
        }
        int a, b;

        if(my_atoi(argv[2], &a)){
            printf("invalid number 2");
            return 2;
        }
        if(my_atoi(argv[3], &b)){
            printf("invalid number 3");
            return 2;
        }
        if(checkMultiple(a, b)){
            printf("%d is a multiple of %d\n", a, b);
        }else{
            printf("%d is not a multiple of %d\n", a, b);
        }
    } else if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "/t") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Error: -t flag requires 4 parameters\n");
            return 1;
        }

        double a, b, c, epsilon;

        if(my_atof(argv[2], &epsilon)){
            printf("invalid number 2");
            return 2;
        }
        if(my_atof(argv[3], &b)){
            printf("invalid number 3");
            return 2;
        }
        if(my_atof(argv[4], &c)){
            printf("invalid number 4");
            return 2;
        }
        if(my_atof(argv[5], &a)){
            printf("invalid number 5");
            return 2;
        }

        if(checkTriangle(a, b, c, epsilon)){
            printf("The numbers can be the sides of a triangle\n");
        }else{
            printf("The numbers can not be the sides of a triangle\n");
        }
    } else {
        fprintf(stderr ,"Unknown flag: %s\n", argv[1]);
        return 3;
    }

    return 0;
}
