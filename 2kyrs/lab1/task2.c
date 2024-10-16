#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <math.h>




double fact(int n) {
       if (n == 0 || n == 1) return 1.0;
       double result = 1.0;
       for (int i = 2; i <= n; ++i) {
           result *= i;
       }
       return result;
}

double comb(int m, int k) {
    if (k < 0 || k > m) return 0.0;
    if (k == 0 || k == m) return 1.0;

    // Используем свойство C(m, k) = C(m, m - k)
    if (k > m - k) k = m - k;

    double result = 1.0;
    for (int i = 1; i <= k; ++i) {
        result *= (double)(m - (k - i)) / (double)i;
        
    }
    return result;
}

double comb1(int m, int k) {
    if (k < 0 || k > m) return 0.0;
    if (k == 0 || k == m) return 1.0;
    printf("%d, %d\n", m, k);
    return exp(lgamma((double)(m + 1)) - (lgamma((double)(k + 1)) + lgamma((double)(m - k + 1))));
}

//лимиты

double expLim(double n){
    if(n == 0){
        return 0;
    }
    return pow(1 + (1.0 / n), n);
}

double piLim(double n){
    if(n == 0){
        return 0;
    }
    return (pow(pow(2, n) * fact(n), 4)) / (n * pow(fact(2 * n), 2));
}

double ln2Lim(double n){
    if(n == 0){
        return 0;
    }
    return n * (pow(2 , 1 / n) - 1);
}

double sqrt2Lim(double n){
    if(n == 0.0){
        return -0.5;
    }
    double xPrev = sqrt2Lim(n - 1);
    return xPrev - (pow(xPrev, 2) / 2.0) + 1;
}

double gammLim(int m, double eps){
    double result = 0.0;

    for (int k = 1; k <= m; k++) {
        double C = comb(m, k);          // C(m, k)
        double log_fact = lgamma(k + 1); // log(k!) 
        double sign = pow(-1, k); // (-1)^k

        double step = sign * (C / (double)k) * log_fact;
        result += step;
    }
    return result;
}



double limForGammaEq(double t){

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

double limit1(double limFunc(), double eps){
    double res = limFunc(1.0);
    double prev = limFunc(0.0);
    for(double n = 2.0; fabs(res - prev) > eps; n++){
        printf(" N - %lf, || tt - %lf\n", n, res - prev);
        prev = res;
        res = limFunc(n);
    }
    printf("HOHO\n");
    return res;
}

double limit(double limFunc(), double eps){
    double n = 1.0;
    double current = limFunc(n);
    int maxSteps = 10;
    while (1)
    {
        n += 1;
        double next = limFunc(n);

        if(fabs(next - current) <= eps){
            return next;
        }

        if(n >= maxSteps){
            return next;
        }

        current = next;
    }
    
}

//уравнения функций)

double expEq(double x){
    return log(x) - 1.0;
}

double piEq(double x){
    printf("PI - %lf\n", cos(x) + 1.0);
    return cos(x) + 1.0;
}

double ln2Eq(double x){
    return exp(x) - 2;
}

double sqrt2Eq(double x){
    return pow(x, 2.0) - 2;
}

double gammEq(double x, double eps){
    return exp(-x) - limit(limForGammaEq, eps);
}



//ряды & произведения

double expCalc(double n){
    return 1.0 / fact(n);
}

double piCalc(double n){
    return (pow(-1, n-1)) / (2 * n - 1);
}

double ln2Calc(double n){
    return (pow(-1, n-1)) / (n);
}

double sqrt2Calc(double k){
    return pow(2, pow(2, -k));
}

double gammCalc(double k){
    return (1.0 / (pow((double) (int) (k), 2))) - (1.0 / k);
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

//функция дихотомии
double dihotomya(double a, double b, double func(), double eps){
    double x = (a + b) / 2.0;
    while((func(b) - func(a)) / 2.0 > eps){
        x = (a + b) / 2.0;
        double fx = func(x);

        if (fx == 0.0){
            break;
        }

        if(func(a) * fx < 0){
            b = x;
        } else {
            a = x;
        }
    }

    return x;
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





// Функция для проверки, является ли строка валидным вещественным числом
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




//функции вычислений
void expResult(double eps, double res[]){

    res[0] = limit(expLim, eps);
    
    res[1] = Calculation(expCalc, eps, 's', 0);

    res[2] = dihotomya(1.0, 4.0, expEq, eps);
}


void piResult(double eps, double res[]){
    res[0] = limit(piLim, eps);

    res[1] = 4 * Calculation(piCalc, eps, 's', 1);

    res[2] = dihotomya(2.0, 5.0, piEq, eps);
}



void ln2Result(double eps, double res[]){
    res[0] = limit(ln2Lim, eps);

    res[1] = Calculation(ln2Calc, eps, 's', 1);

    res[2] = dihotomya(0.0, 1.0, ln2Eq, eps);
}


void sqrt2Result(double eps, double res[]){
    res[0] = limit(sqrt2Lim, eps);
    
    res[1] = Calculation(sqrt2Calc, eps, 'm', 2);

    res[2] = dihotomya(1.0, 2.0, sqrt2Eq, eps);
}


void gammResult(double eps, double res[]){
    res[0] = limit(gammLim, eps);

    res[1] = -((pow(3.14159, 2)) / 6) + Calculation(gammCalc, eps, 'm', 2);

    res[2] = dihotomyaForGamma(-100.0, 100.0, gammEq, eps);
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

    if(eps == 0.0){
        fprintf(stderr ,"слишком маленькая епсилон\n");
        return 4;
    }
    
    double Result[3];
    expResult(eps, Result);
    printf("exp - %lf %lf %lf\n", Result[0], Result[1], Result[2]);

    piResult(eps, Result);
    printf("pi - %lf %lf %lf\n", Result[0], Result[1], Result[2]);

    ln2Result(eps, Result);
    printf("ln(2) - %lf %lf %lf\n", Result[0], Result[1], Result[2]);

    sqrt2Result(eps, Result);
    printf("sqrt(2) - %lf %lf %lf\n", Result[0], Result[1], Result[2]);

    gammResult(eps, Result);
    printf("gamma - %lf %lf %lf\n", Result[0], Result[1], Result[2]);

    return 0;
}
