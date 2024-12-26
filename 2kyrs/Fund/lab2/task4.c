#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int isConvexPolygon(int numberOfVertices, ...) {
    if (numberOfVertices < 3) return 0; 

    va_list args;
    va_start(args, numberOfVertices);

    double x1, y1, x2, y2, x3, y3;
    x1 = va_arg(args, double);
    y1 = va_arg(args, double);
    x2 = va_arg(args, double);
    y2 = va_arg(args, double);

    int concave = 0;
    for (int i = 0; i < numberOfVertices - 2; i++) {
        x3 = va_arg(args, double);
        y3 = va_arg(args, double);

        double crossProduct = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
        if (crossProduct < 0) concave = 1;

        x1 = x2;
        y1 = y2;
        x2 = x3;
        y2 = y3;
    }

    va_end(args);
    return !concave;
}


double evaluatePolynomial(double x, int n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0;
    for (int i = 0; i <= n; i++) {
        double coefficient = va_arg(args, double);
        result += coefficient * pow(x, n - i);
    }

    va_end(args);
    return result;
}

int isKaprekarNumber(int number, int base) {
    int square = number * number;
    char squareStr[50];
    snprintf(squareStr, 50, "%d", square);

    int len = strlen(squareStr);
    for (int i = 1; i < len; i++) {
        char leftStr[50] = {0}, rightStr[50] = {0};
        strncpy(leftStr, squareStr, i);
        strcpy(rightStr, squareStr + i);

        int left = atoi(leftStr);
        int right = atoi(rightStr);

        if (right > 0 && left + right == number) {
            return 1;
        }
    }
    return 0;
}

void findKaprekarNumbers(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        char* numStr = va_arg(args, char*);
        int number = strtol(numStr, NULL, base);
        
        if (isKaprekarNumber(number, base)) {
            printf("%s is a Kaprekar number\n", numStr);
        } else {
            printf("%s is not a Kaprekar number\n", numStr);
        }
    }

    va_end(args);
}

int main() {
    
    printf("Polygon is convex: %d\n", isConvexPolygon(4, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0));

    
    printf("Value of polynomial: %f\n", evaluatePolynomial(2.0, 2, 3.0, 2.0, 1.0));

    
    findKaprekarNumbers(10, 3, "9", "45", "297");

    return 0;
}