#include <stdio.h>
#include <stdarg.h>
#include <math.h>


double geometric_mean(int count, ...) {
    va_list args;
    va_start(args, count);
    
    double product = 1.0;
    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        product *= num;
    }
    
    va_end(args);
    
    return pow(product, 1.0 / count);
}


double power(double base, int exp) {
    if (exp == 0) return 1;
    if (exp < 0) return 1 / power(base, -exp);
    
    double half = power(base, exp / 2);
    if (exp % 2 == 0) {
        return half * half;
    } else {
        return half * half * base;
    }
}

int main() {
    
    printf("Geometric mean: %f\n", geometric_mean(3, 2.0, 3.0, 4.0));
    
    printf("Power: %f\n", power(2.0, 5));
    return 0;
}