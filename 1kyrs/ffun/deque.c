#include <stdio.h>
#include <stdbool.h>
const int max_capacity = 10;

typedef struct{
    int size;
    int first;
    double buffer[max_capacity];
} deque;

void deque_create(deque *dq){
    dq -> size = 0;
    dq -> first = 0;
}
void deque_destroy(deque *dq){
    dq -> size = 0;
    dq -> first = 0;
}
bool deque_push_back(deque *dq ,double a){
    if(dq -> size == max_capacity) return false;
    dq -> buffer[(dq -> first + dq -> size) % max_capacity] = a;
    dq -> size++;
}
double deque_pop_front(deque *dq){
    if(dq -> size == 0) return __DBL_MAX__;
    double var = dq->buffer[dq->first];
    dq->size--;
    return var;
}
bool deque_push_front(deque *dq ,double a){
    if(dq -> size == max_capacity) return false;
    dq -> first = (dq -> first - 1 + max_capacity) % max_capacity;
    dq -> buffer[dq -> first] = a;
    dq -> size++;
    return true;
}
double deque_pop_back(deque *dq){
    if(dq -> size == 0) return __DBL_MAX__;
    dq->size--;
    return dq -> buffer[(dq -> first + dq -> size) % max_capacity];
}

bool deque_is_empty(deque *dq){
    return dq -> size == 0;
}

