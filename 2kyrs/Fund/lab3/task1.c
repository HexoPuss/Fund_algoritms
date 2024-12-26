#include <stdio.h>

void convertToBase(int number, int r) {
    unsigned int base = 1 << r; 
    char result[32];
    int i = 0;

    while (number > 0) {
        int remainder = number & (base - 1);
        number >>= r; 
        result[i++] = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
    }


    while (i > 0) {
        printf("%c", result[--i]);
    }
    printf("\n");
}

int main() {
    int decimalNumber = 0;
    for (int r = 1; r <= 5; r++) {
        printf("Число %d в системе с основанием 2^%d: ", decimalNumber, r);
        convertToBase(decimalNumber, r);
    }
    return 0;
}