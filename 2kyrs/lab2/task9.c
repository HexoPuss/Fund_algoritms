#include <stdio.h>
#include <math.h>
#include <stdarg.h>

int isPrime(int n) {
    if (n > 1) {
        for (int i = 2; i < n; i++)
            if (n % i == 0)
                return 0;
        return 1;
    } else
        return 0;
}


unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long getDenominator(double number) {
    if (number <= 0 || number >= 1) {
        return 0;
    }
    double epsilon = 0000.1;
    unsigned long long denominator = 1;
    unsigned long long numerator = 1;

    while (fabs((number * denominator) - floor(number * denominator))) {
        denominator *= 10;
        
    }

    numerator = (unsigned long long)(number * denominator);

    unsigned long long divisor = gcd(numerator, denominator);
    
    
    denominator /= divisor;

    return denominator;
}

int hasFiniteRepresentation(double number, int base){
    unsigned long long denom = getDenominator(number);
    unsigned long long mult = 1;
    while (denom != 1.0){
        for(int i = 2;i <= denom; i++){
            if(denom % i == 0){
                if(isPrime(i)){
                    mult *= i;
                }
                while (denom % i == 0){
                    denom /= i;
                }
                
                break;
            }
        }
    }
    return (base % mult == 0);
    
}

int checkRepresentation(int base, int n, ...){
    va_list args;
    va_start(args, n);
    
    for (int i = 0; i < n; i++) {
        double number = va_arg(args, double);
        if(number >= 1 || number <= 0){
            return 1;
        }
        
        if (hasFiniteRepresentation(number, base)) {
            printf("Число %f имеет конечное представление в базе %d\n", number, base);
        } else {
            printf("Число %f не имеет конечного представления в базе %d\n", number, base);
        }
    }
    
    va_end(args);
    return 0;

}

int main() {
    checkRepresentation(16, 1, 0.125);
}