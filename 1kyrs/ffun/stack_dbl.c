#include <stdbool.h>

Typedef struct{
	double buffer[max_capacity];
	int size;
} stack_dbl;

void stack_dbl_create(stack_dbl *s){
    s -> size = 0;
    for (size_t i = 0; i < max_capacity; i++){
        s -> buffer[i] = 0;
    }
}

void stack_dbl_size(stack_dbl *s){
    return s -> size;
}

void stack_dbl_destroy(stack_dbl *s){
    s -> size = 0;
}

bool stack_dbl_is_empty(stack_dbl *s){
    return (s - > size == 0);
}

bool stack_dbl_push(stack_dbl *s, double a){
    if(s -> size >= max_capacity){
        return false
    }
    s -> buffer[s -> size ++] = a;
    return true
}

double stack_dbl_pop(stack_dbl *s){
    is (s -> size != 0){
        double t = s -> buffer[s -> size];
        s -> size--;
        return t;
    }
    return max_int;
}