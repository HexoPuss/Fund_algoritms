#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum CASES {
    CASE_H,
    CASE_P,
    CASE_S,
    CASE_E,
    CASE_A,
    CASE_F
} CASES;

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
    if(x <= 1){
        return 0;
    }

    for(int i = 2; i < x / 2; i++){
        if(x % i == 0){
            return 0;
            break;
        }
    }

    return 1;
}

int caseS(int x){
    if(x == 0){
        printf("0\n");
        return 0;
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
    
    return 0;
}

int caseE(int x){
    if(x > 10){
        printf("x должен быть не мольше 10!\n");
        return 0;
    }

    for (int i = 2; i <= 10; i++){
        for(int j = 1; j <= x; j++){
            printf(" %d", intpow(i, j));
        }
        printf("\n");
    }
    return 0;
}

int caseA(int x){
    if(x < 1){
        printf("0\n");
        return 0;
    }
    int res = ((1 + x) / 2.0) * x;
    if(x % 2 == 0){
        res += x / 2;
    }
    printf("%d", res);
}

int caseF(int x){
    if(x < 0){
        printf("факториала от отрицательных чисел не сущесвует");
        return -1;
    }
    int fact = 1;
    for(int i = 1; i <= x; i++){
        fact *= i;
    }
    printf("%d\n", fact);
}

int CheckFlag(const char* flag, char* valid_flag) {
	return (flag[0] == '-' || flag[0] == '/') && strcmp(&flag[1], valid_flag) == 0;
}

int GetOpts(int argc, char** argv, CASES* option, int* x) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <flag> <x>\n", argv[0]);
		return 1;
	}

	if(my_atoi(argv[2], x)){
        return 2;
    }

	char* flags[6] = {"h", "p", "s", "e", "a", "f"};

	for (int i = 0; i < 6; i++) {
		if (CheckFlag(argv[1], flags[i])) {
			*option = i;
			return 0;
		}
	}

	return 3;
}

int main(int argc, char *argv[]) {
    // Проверяем, что передано минимум 2 аргумента (программа + минимум 1 параметр)
    if (argc != 3) {
        fprintf(stderr , "некорректное число аргументов");
        return 1;
    }

    CASES opt = 0;
    int x = 0;
    int result;

    void (*functions[4])(int) = {caseH, caseP, caseS, caseE, caseA, caseF};
	char* flags[6] = {"h", "p", "s", "e", "a", "f"};

	int res = GetOpts(argc, argv, &opt, &x);
	switch (res) {
		case 0:
			break;
		case 1:
			printf("Incorrect number of arguments.\n");
			return 1;
		case 2:
			printf("Error: %s or %s aren't a double number.\n", argv[2], argv[3]);
			return 1;
		case 3:
			printf("Unknown flag: %s\n", argv[1]);
			return 1;
		default:
			printf("Unknown error.\n");
			return 1;
	}

	functions[opt](x);

	return 0;

    
}
