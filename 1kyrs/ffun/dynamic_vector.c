#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    double* buffer;
    size_t capacity;
    size_t size;
} vector_dbl;

void create_vector_dbl(vector_dbl *v){
    v -> buffer = NULL;
    v -> capacity = 0;
    v->size = 0;
}
void destroy_vector_dbl(vector_dbl *v){

}
double get_vector_dbl(vector_dbl *v, size_t index){

}
void set_vector_dbl(vector_dbl *v, size_t index, double el){

}
bool resize_vector_dbl(vector_dbl *v, size_t new_size){

}
bool push_back_vector_dbl(vector_dbl *v, double val){
    if(v->capacity == v->size){
        if(!grow_buffer(v)){
            return false;
        }
    }
    v->buffer[++(v->size)] = val;
    return true;
}
double pop_back_vector_dbl(vector_dbl *v){
    if(v->size == (4/9)*v->capacity){
        srink_buffer(v);
    }
    double t = v->buffer[v->size--];
    v->buffer[v->size] = 0;
    return t;
}
bool resize_vector_dbl(vector_dbl *v, size_t new_size){
    if(new_size > v->capacity){
        double* newbuf = realloc(v->buffer, new_size * sizeof(double));
        if(newbuf == NULL){return false;}
        v->buffer = newbuf;
        v->capacity = new_size;
    }
    for(size_t i = new_size; i < v->size; i++){
        v->buffer[i] = 0;
    }
    v->size = new_size;
    return true;
}