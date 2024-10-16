#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

long double fact(int n){
    if (n == 0 || n == 1) return 1.0;
    long double result = 1.0;
   for (int i = 2; i <= n; ++i) {
       result *= i;
   }
    return (long double) result;
}

long double fracFact(int a, int b){
    //a! / b!
    long double res = 1;
    if(a >= b){
        for(int i = b + 1; i <= a; i++){
            res *= i;
        }
    }else{
        return 1.0 / fracFact(b, a);
    }
    return res;
}

long double factfact(int n){
    if(n == 0 || n == 1){
        return 1;
    }
    int even = n % 2;
    int res = 1;
    for(int i = 2; i <= n; i++){
        if (i % 2 == even){
            res *= i;
        }
    }
}

long double Calculation(long double calc(), long double eps, long double x, long double nStart){
    long double prev;
    long double res;
    long double n = nStart;
    prev = 0;
    res = 0;
    do{
        prev = res;
        res = prev + calc(n, x);
        n++;
    }while(fabs(res - prev) > eps);

    return res;
}

long double sumA(int n, long double x){
    return (pow(x, (long double) n)) / (fact(n));
}

long double sumB(int n,long double x){
    return (pow(-1, (long double) n) * pow(x, ((long double) n) * 2.0) / (fact(2 * n)));
}

long double sumC(int intn, long double x){
    long double n = (long double) n;
    return (pow(3.0, 3 * n) * pow(fact(intn), 2) * (pow(x, 2 * n))) * fracFact(intn, 3 * intn);
}

long double sumD(int intn, long double x){
    long double n = (long double) n;
    return pow(-1, n) * factfact(intn * 2 - 1) * pow(x, 2 * n) / factfact(2 * n);
}

int isValidDouble(const char *str, long double *out_value) {
    char *endptr;
    errno = 0;
    long double val = strtod(str, &endptr);

    if (errno != 0) {
        return 0;
    }

    *out_value = val;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: eps, x\n");
        return 1;
    }

    long double eps;
    long double xVar;
    if (!isValidDouble(argv[1], &eps)) {
        fprintf(stderr, "Ошибка: '%s' не является допустимым вещественным числом.\n", argv[1]);
        return 2;
    }
    if (!isValidDouble(argv[1], &xVar)) {
        fprintf(stderr, "Ошибка: '%s' не является допустимым вещественным числом.\n", argv[1]);
        return 2;
    }

    long double res = Calculation(sumA, eps, xVar, 0);
    printf("f - %Lf\n", res);

    /*res = Calculation(sumB, eps, xVar, 0);
    printf("b - %Lf\n", res);

    res = Calculation(sumC, eps, xVar, 0);
    printf("c - %Lf\n", res);

    res = Calculation(sumD, eps, xVar, 1);
    printf("d - %Lf\n", res);*/
    

    return 0;
}