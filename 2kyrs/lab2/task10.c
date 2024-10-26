#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

long GetBinCoeff(long N, long K)
{
   long r = 1;
   long d;
   if (K > N) return 0;
   for (d = 1; d <= K; d++)
   {
      r *= N--;
      r /= d;
   }
   return r;
}
\
void polynomialExpansion(double epsilon, double a, double **g, int degree, ...) {
    va_list args;
    va_start(args, degree);
    
    double *f = (double *)malloc((degree + 1) * sizeof(double));
    for (int i = 0; i <= degree; i++) {
        f[i] = va_arg(args, double);
    }

    *g = (double *)malloc((degree + 1) * sizeof(double));

    for (int i = 0; i <= degree; i++) {
        (*g)[i] = 0.0;
        for (int j = i; j <= degree; j++) {
            (*g)[i] += f[j] * GetBinCoeff(degree, j) * pow(a, j - i);
        }
    }

    va_end(args);
    
    free(f);
}

int main() {
    double *g;
    int degree = 4;
    double epsilon = 0.001;
    double a = 1.0;
    
    polynomialExpansion(epsilon, a, &g, degree, 1.0, 2.0, 3.0, 13.0, 44.0);

    printf("Коэффициенты многочлена (x - a):\n");
    for (int i = 0; i <= degree; i++) {
        printf("g[%d] = %f\n", i, g[i]);
    }

    free(g);

    return 0;
}