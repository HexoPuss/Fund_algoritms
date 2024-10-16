#include <stdio.h>
#include <stdbool.h>


typedef struct{
    double *buf;
    int size;
    int buf_size;
} stack;

void sd_create(stack *s){
    s -> size = 0;
    s -> buf_size = 0;
    s -> buf = NULL;
}
void sd_destroy(stack *s){
    s -> size = 0;
    s -> buf_size = 0;
    if (s -> buf != NULL){
        free(s -> buf);
    }
}
bool sd_push(stack *s, double a){
    // if(s -> buf_size == s -> size){
    //     double* newbuf = realloc(s -> buf, sizeof(double) * s -> size * 2);
    //     if (newbuf == NULL){return false;}
    //     s -> buf_size = s -> buf_size * 2;
    //     s -> buf = newbuf;
    // }
    if (s -> size == s -> buf_size){
        if(!sd_growbuf(s)) return false;
    }
    s -> buf[s -> size] = a;
    s -> size++;
    return true;
}

bool sd_isempty(stack *s){
    return s -> size == 0;
}

double sd_pop(stack *s){
    if(s -> size == 0){return __DBL_MAX__;}
    double var = s -> buf[s -> size - 1];
    s -> size--;
}

bool sd_growbuf(stack *s){
    int t = s -> size * 3/2 * (s -> buf_size >= 2) + 2 * (s -> buf_size < 2);
    double* newbuf = realloc(s -> buf, sizeof(double) * t);
    if (newbuf == NULL) return false;
    s -> buf = newbuf;
    s -> buf_size = t;
    return true;
}   