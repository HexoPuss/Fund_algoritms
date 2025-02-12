#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdarg.h>
#include <limits.h>

#define MAX_LENGTH 1000000

typedef struct {
    char* text;
    char* pattern;
    int start;
    int end;
    int* results;
    int* result_count;
    pthread_mutex_t* mutex;
} ThreadData;



void write_number_double(int fd, double num, int precision) {
    char buffer[64];
    int pos = 0;

    // Обработка отрицательных чисел
    if (num < 0) {
        buffer[pos++] = '-';
        num = -num;
    }

    // Извлечение целой части
    long long int_part = (long long)num;
    double fractional = num - (double)int_part;

    // Преобразование целой части в строку
    char int_buffer[32];
    int int_pos = 0;
    if (int_part == 0) {
        int_buffer[int_pos++] = '0';
    } else {
        while (int_part > 0 && int_pos < (int)(sizeof(int_buffer) - 1)) {
            int_buffer[int_pos++] = '0' + (int)(int_part % 10);
            int_part /= 10;
        }
    }
    // Инвертирование целой части
    for (int i = int_pos - 1; i >= 0; i--) {
        buffer[pos++] = int_buffer[i];
    }

    // Добавление десятичной точки
    buffer[pos++] = '.';

    // Обработка дробной части
    for (int i = 0; i < precision; i++) {
        fractional *= 10;
    }
    long long frac_part = (long long)(fractional + 0.5); // Округление
    // Преобразование дробной части в строку с ведущими нулями
    char frac_buffer[32];
    int frac_pos = 0;
    for (int i = precision - 1; i >= 0; i--) {
        frac_buffer[i] = '0' + (frac_part % 10);
        frac_part /= 10;
    }
    for (int i = 0; i < precision; i++) {
        buffer[pos++] = frac_buffer[i];
    }

    // Отправка строки через write
    write(fd, buffer, pos);
}

void write_number(int fd, int num) {
    char buffer[20];
    int len = 0;
    if (num == 0) {
        write(fd, "0", 1);
        return;
    }
    while (num > 0) {
        buffer[len++] = '0' + (num % 10);
        num /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        write(fd, &buffer[i], 1);
    }
}

void* search_pattern(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    for (int i = data->start; i <= data->end - strlen(data->pattern) + 1; i++) {
        int match = 1;
        for (int j = 0; j < strlen(data->pattern); j++) {
            if (data->text[i + j] != data->pattern[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            pthread_mutex_lock(data->mutex);
            data->results[*data->result_count] = i;
            (*data->result_count)++;
            pthread_mutex_unlock(data->mutex);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        write(2, "Usage: program <max_threads> <pattern>\n", 38);
        return 1;
    }

    int max_threads = atoi(argv[1]);
    char* pattern = argv[2];
    char text[MAX_LENGTH];
    int text_len = 0;
    char c;
    
    while (read(0, &c, 1) > 0 && text_len < MAX_LENGTH - 1) {
        text[text_len++] = c;
    }
    text[text_len] = '\0';
    if(strlen(text) < strlen(pattern)){
        write(2, "Too big pattern for this text", 30);
    }

    //struct timespec start, end;
    //clock_gettime(CLOCK_MONOTONIC, &start);

    int results[MAX_LENGTH];
    int result_count = 0;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t* threads = malloc(max_threads * sizeof(pthread_t));
    ThreadData* thread_data = malloc(max_threads * sizeof(ThreadData));

    int chunk_size = text_len / max_threads;
    
    for (int i = 0; i < max_threads; i++) {
        thread_data[i].text = text;
        thread_data[i].pattern = pattern;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == max_threads - 1) ? text_len : (i + 1) * chunk_size;
        thread_data[i].results = results;
        thread_data[i].result_count = &result_count;
        thread_data[i].mutex = &mutex;

        pthread_create(&threads[i], NULL, search_pattern, &thread_data[i]);
    }

    for (int i = 0; i < max_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    write(1, "\nFound positions: ", 17);
    for (int i = 0; i < result_count; i++) {
        write_number(1, results[i]);
        write(1, " ", 1);
    }
    write(1, "\n", 1);

    free(threads);
    free(thread_data);
    pthread_mutex_destroy(&mutex);

    
    return 0;
}







/*clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = end.tv_sec - start.tv_sec;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    write_number_double(1, elapsed, 6);*/
    //write(1, "\n", 1);