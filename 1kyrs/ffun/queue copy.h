typedef struct{
    int size;
    int max_capacity = 10;
    int first;
    double buffer[MAX_CAP];
} queue_dbl;

void queue_dbl_create(queue_dbl *q);
void queue_dbl_destroy(queue_dbl *q);
bool queue_dbl_push(queue_dbl *q ,double a);
double queue_dbl_pop(queue_dbl *s, queue_dbl *s);
bool queue_dbl_is_empty(queue_dbl *s);

