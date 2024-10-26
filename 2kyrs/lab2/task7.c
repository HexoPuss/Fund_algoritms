#include <stdio.h>
#include <math.h>

double exampleFunction(double x) {
    return x * x - 4;
}

double dichotomyMethod(double (*func)(double), double a, double b, double epsilon) {
    double middle;
    while ((b - a) / 2 > epsilon) {
        middle = (a + b) / 2;
        if (func(middle) == 0.0) {
            return middle;
        } else if (func(a) * func(middle) < 0) {
            b = middle;
        } else {
            a = middle;
        }
    }
    return (a + b) / 2;
}

int main() {
    double a = 0; 
    double b = 5;
    double epsilon = 0.01;

    double root = dichotomyMethod(exampleFunction, a, b, epsilon);
    printf("Найденный корень: %lf\n", root);

    return 0;
}