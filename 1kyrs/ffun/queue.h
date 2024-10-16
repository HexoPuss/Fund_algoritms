#include <stdio.h>
#include <stdbool.h>
const int max_capacity = 10;

typedef struct{
    int size;
    int first;
    double buffer[max_capacity];
} qd;

void qd_create(qd *q){
    q -> size = 0;
    q -> first = 0;
}
void qd_destroy(qd *q){
    q -> size = 0;
    q -> first = 0;
}
bool qd_push(qd *q ,double a){
    if(q -> size == max_capacity) return false;
    q -> buffer[(q -> first + q -> size) % max_capacity] = a;
    q -> size++;
}
double qd_pop(qd *q){
    if(q -> size == 0) return __DBL_MAX__;
    double var = q->buffer[q->first];
    q->size--;
    return var;
}
bool qd_is_empty(qd *q){
    return q -> size == 0;
}

