#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

int compareFloats(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

void solveQuadratic(double a, double b, double c, double epsilon) {
    double discriminant = b*b - 4*a*c;
    if (compareFloats(discriminant, 0, epsilon)) {
        double root = -b / (2*a);
        printf("One double root: %.2lf\n", root);
    } else if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2*a);
        double root2 = (-b - sqrt(discriminant)) / (2*a);
        printf("Two roots: %.2lf, %.2lf\n", root1, root2);
    } else {
        printf("No real roots.\n");
    }
}

void checkMultiple(int a, int b) {
    if (b != 0 && a % b == 0) {
        printf("%d is a multiple of %d\n", a, b);
    } else {
        printf("%d is not a multiple of %d\n", a, b);
    }
}

void checkTriangle(double a, double b, double c, double epsilon) {
    if (compareFloats(a*a + b*b, c*c, epsilon) ||
        compareFloats(a*a + c*c, b*b, epsilon) ||
        compareFloats(b*b + c*c, a*a, epsilon)) {
        printf("The numbers can be the sides of a triangle\n");
    } else {
        printf("The numbers cannot be the sides of a triangle\n");
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
    
    errno = 0;

    if (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "/q") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Error: -q flag requires 4 parameters\n");
            return 1;
        }
        double vars[3];
        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);
        
        if(errno != 0){
            fprintf(stderr, "Error: invalid number\n");
            return 2;
        }

        vars[0] = a;
        vars[1] = b;
        vars[2] = c;
        int perm[6];
        permutations(a, b, c, perm);
        for(int i = 0; i < 6; i++){
            printf("for %lfx^2 + %lfx + %lf: ", vars[(perm[i] / 100) - 1], vars[((perm[i] % 100) / 10) - 1], vars[(perm[i] % 10) - 1]);
            solveQuadratic(vars[(perm[i] / 100) - 1], vars[((perm[i] % 100) / 10) - 1], vars[(perm[i] % 10) - 1], epsilon);
        }
        
    } else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "/m") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: -m flag requires 2 parameters\n");
            return 1;
        }
        int a = atoi(argv[2]);
        int b = atoi(argv[3]);
        if(errno != 0){
            fprintf(stderr, "Error: invalid number\n");
            return 2;
        }
        checkMultiple(a, b);
    } else if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "/t") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Error: -t flag requires 4 parameters\n");
            return 1;
        }
        double epsilon = atof(argv[2]);
        double a = atof(argv[3]);
        double b = atof(argv[4]);
        double c = atof(argv[5]);
        if(errno != 0){
            fprintf(stderr, "Error: invalid number\n");
            return 2;
        }
        checkTriangle(a, b, c, epsilon);
    } else {
        fprintf(stderr ,"Unknown flag: %s\n", argv[1]);
        return 3;
    }

    return 0;
}
