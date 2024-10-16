#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 

typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int size;
} Deque;

typedef struct{
    int size;
    int front;
    int rear;
    Deque* arr[MAX_SIZE];
} deq;

// Function prototypes (for Deque)
void initializeDeque(Deque* deque);
void displayDeque(const Deque* deque);
int getSize(const Deque* deque);
void insertFront(Deque* deque, int value);
void insertRear(Deque* deque, int value);
void deleteFront(Deque* deque);
void deleteRear(Deque* deque);
void clearDeque(Deque* deque);

// for deq
void initDeq(deq* dq);
void insertFrontDeq(Deque* deque, int value);
void insertRearDeq(Deque* deque, int value);
void deleteFrontDeq(Deque* deque);
void deleteRearDeq(Deque* deque);
void clearDeq(Deque* deque);

#endif