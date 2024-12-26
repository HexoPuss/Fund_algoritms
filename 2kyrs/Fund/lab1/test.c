#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


double comb(int m, int k) {
    if (k < 0 || k > m) return 0.0;
    if (k == 0 || k == m) return 1.0;
    //printf("%d, %d\n", m, k);
    return exp(lgamma((double)(m + 1)) - (lgamma((double)(k + 1)) + lgamma((double)(m - k + 1))));
}


double limForGammaEq(double t, double eps){


    int simpNums[((int) t) + 1];
    for (int i = 1; i <= t; i++){
        simpNums[i] = i;
    }


    for(int i = 2; i <= t / 2; i++){
        for(int j = 1; j <= t; j++){
            if(simpNums[j] % i != 0){
                simpNums[j] = 0;
            }
        }
    }

    double mult = 1;

    for(int i = 2; i <= t; i++){
        if (simpNums[i] != 0){
            mult *= (((double) simpNums[i]) - 1) / (simpNums[i]);
        }
    }

    return log(t) * mult;
}



double gammLim(int m, double eps){
    double result = 0.0;
    for (int k = 1; k <= m; k++) {
        printf("%d, %d ___\n", m, k);
        break;
        double C = comb(m, k);          // C(m, k)
        if(fabs(C) < 10000){
            printf("|%lf|, %d, %d\n", C, m, k);
        }
        double log_fact = lgamma(k + 1); // log(k!) 
        double sign = pow(-1, k); // (-1)^k

        double step = sign * (C / (double)k) * log_fact;
        result += step;
    }
    return result;
}

double gammCalc(double k){
    return (1.0 / (pow((double) (int) (k), 2))) - (1.0 / k);
}



double limit(double limFunc(), double eps){
    double n = 1.0;
    double current = limFunc(n);
    while (1)
    {
        n += 1;
        double next = limFunc(n);

        if(fabs(next - current) <= eps){
            return next;
        }

        current = next;
    }
    
}

double gammEq(double x, double eps){
    return exp(-x) - limit(limForGammaEq, eps);
}

double Calculation(double calc(), double eps, char flag, double nStart){
    double prev;
    double res;
    double n = nStart;
    if(flag == 's'){
        prev = 0;
        res = 0;
        do{
            prev = res;
            res = prev + calc(n);
            n++;
        }while(fabs(res - prev) > eps);
    }else{
        prev = 1;
        res = 1;
        do{
            prev = res;
            res = prev * calc(n);
            n++;
        }while(fabs(res - prev) > eps);
    }

    return res;
}

double dihotomyaForGamma(double a, double b, double func(), double eps){
    double x = (a + b) / 2.0;
    while((b - a) / 2.0 > eps){
        x = (a + b) / 2.0;
        double fx = func(x, eps);

        if (fx == 0.0){
            break;
        }

        if(func(a, eps) * fx < 0){
            b = x;
        } else {
            a = x;
        }
    }

    return x;
}



void gammResult(double eps, double res[]){
    res[0] = limit(gammLim, eps);

    res[1] = -((pow(3.14159, 2)) / 6) + Calculation(gammCalc, eps, 'm', 2);

    res[2] = dihotomyaForGamma(-100.0, 100.0, gammEq, eps);
}

int isValidDouble(const char *str, double *out_value) {
    char *endptr;
    errno = 0; // Сбрасываем errno перед вызовом
    double val = strtod(str, &endptr);

    // Проверяем, произошла ли ошибка при конвертации
    if (errno != 0) {
        return 0;
    }

    *out_value = val;
    return 1;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <вещественное число>n", argv[0]);
        return 1;
    }

    double eps;
    if (!isValidDouble(argv[1], &eps)) {
        fprintf(stderr, "Ошибка: '%s' не является допустимым вещественным числом.n", argv[1]);
        return 2;
    }
    
    double Result[3];

    gammResult(eps, Result);

    
    printf("gamma - %lf %lf %lf\n", Result[0], Result[1], Result[2]);
    //free(Result);
    return 0;
}
