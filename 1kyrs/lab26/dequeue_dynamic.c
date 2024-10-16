#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int size;
    int first;
    double* buffer;
    int capacity;
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
    if(dq -> size == dq -> capacity) return false;
    dq -> buffer[(dq -> first + dq -> size) % dq -> capacity] = a;
    dq -> size++;
}
bool deque_push_front(deque *dq ,double a){
    if(dq -> size == dq -> capacity){
        if(!deque_growbuf(dq)) return false;
    }
    dq -> first = (dq -> first - 1 + dq -> capacity) % dq -> capacity;
    dq -> buffer[dq -> first] = a;
    dq -> size++;
    return true;
}
double deque_pop_back(deque *dq){
    if(dq -> size == 0) return __DBL_MAX__;
    dq->size--;
    return dq -> buffer[(dq -> first + dq -> size) % dq -> capacity];
}
double deque_pop_front(deque *dq){
    if(dq -> size == 0) return __DBL_MAX__;
    double var = dq->buffer[dq->first];
    dq->size--;
    return var;
}
bool deque_push(deque *d, double a){
    if(d -> size == d->capacity){
        if(!deque_growbuf(d)) return false;
    }
    d->buffer[(d->first + d->size) % d->capacity] = a;
    d->size++;
    return true;
}

bool deque_growbuf(deque *d){
    int new_cap = d->capacity * 3/2;
    if(new_cap == d->capacity){new_cap = 4;}
    double *new_buf = realloc(d->buffer, sizeof(double) * new_cap);
    if(new_buf == NULL){return false;}
    d->buffer = new_buf;
    
    for(int i; i < d->capacity - d->first; i++){
        d->buffer[new_cap - i] = d->buffer[d->capacity - i];
    }
    d->first += new_cap - d->capacity;
    d->capacity = new_cap;
    return true;
}

bool deque_is_empty(deque *dq){
    return dq -> size == 0;
}

