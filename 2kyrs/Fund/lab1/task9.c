#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swapMaxMin(int *arr, int size) {
    int max_index = 0, min_index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    int temp = arr[max_index];
    arr[max_index] = arr[min_index];
    arr[min_index] = temp;
}

int closestElement(int num, int *arr, int size) {
    int closest = arr[0];
    for (int i = 1; i < size; i++) {
        if (abs(arr[i] - num) < abs(closest - num)) {
            closest = arr[i];
        }
    }
    return closest;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <lower_bound> <upper_bound>\n", argv[0]);
        return 1;
    }

    int lower = atoi(argv[1]);
    int upper = atoi(argv[2]);
    int size = 10;
    int fixedArray[size];

    srand(time(NULL));
    
    // Filling fixed-size array
    for (int i = 0; i < size; i++) {
        fixedArray[i] = lower + rand() % (upper - lower + 1);
    }

    printf("Original Fixed Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", fixedArray[i]);
    }
    printf("\n");

    swapMaxMin(fixedArray, size);

    printf("Modified Fixed Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", fixedArray[i]);
    }
    printf("\n");

    // Dynamic arrays
    int sizeA = 10 + rand() % 991;
    int sizeB = 10 + rand() % 991;
    int *A = malloc(sizeA * sizeof(int));
    int *B = malloc(sizeB * sizeof(int));
    if(!A || !B){
        fprintf(stderr, "malloc error\n");
        return 2;
    }

    for (int i = 0; i < sizeA; i++) {
        A[i] = -1000 + rand() % 2001;
    }

    for (int i = 0; i < sizeB; i++) {
        B[i] = -1000 + rand() % 2001;
    }

    int *C = malloc(sizeA * sizeof(int));
    for (int i = 0; i < sizeA; i++) {
        C[i] = A[i] + closestElement(A[i], B, sizeB);
    }

    printf("Array A: ");
    for (int i = 0; i < sizeA; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("Array C: ");
    for (int i = 0; i < sizeA; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}
