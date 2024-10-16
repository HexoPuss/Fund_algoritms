#include <stdio.h>
#include <stdbool.h>
// типо все написали
Typedef struct{
	double buffer[max_capacity];
	int size;
} stack_dbl;

void stack_dbl_create(stack_dbl *s);
void stack_dbl_destroy(stack_dbl *s);
int stack_dbl_size(stack_dbl *s);
bool stack_dbl_push(stack_dbl *s, double a);
double stack_dbl_pop(stack_dbl *s);
bool stack_dbl_is_empty(stack_dbl *s);

int main(){
    stack_dbl s;
    stack_dbl_create(&s);
    double input;
    while (scanf("%lf", &input) == 1)
    {
        if (!stack_dbl_push(&s, input)){
            fprintf(stderr, "stack is full");
            return -1
        }
    }
    while (!stack_dbl_is_empty(&s)){
        printf("%ld\n", stack_dbl_pop(&s))
    }
    stack_dbl_destroy(&s);
}
