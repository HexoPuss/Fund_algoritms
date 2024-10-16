#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deque.c"

void printChoose() { //вывод выбора действий
    printf("\nВыберите действие:\n");
    printf("0)Выход\n");
    printf("1)Создать рандомный дек\n");
    printf("2)Вывести содержимое дека\n");
    printf("3)бинарный поиск (введите 3 <value>)\n");
    printf("4)Вставить элемент в начало\n");
    printf("5)Вставить элемент в конец\n");
    printf("6)Удалить первый элемент\n");
    printf("7)Удалить последний элемент\n");
    printf("8)Сортировка\n");
    printf("9)Опустошить дек\n");
}


Deque* Merge(Deque* dq1, Deque* dq2){
    if(dq1 == NULL){return dq2;}
    if(dq2 == NULL){return dq1;}

    Deque res;
    initializeDeque(&res);
    int size = dq1->size + dq2->size;
    while(res.size < (size)){
        if(dq1->size == 0){
            insertRear(&res, dq2->arr[dq2->front]);
            deleteFront(dq2);
        } else if(dq2->size == 0){
            insertRear(&res, dq1->arr[dq1->front]);
            deleteFront(dq1);
        }else
        if(dq1->arr[dq1->front] < dq2->arr[dq2->front]){
            insertRear(&res, dq1->arr[dq1->front]);
            deleteFront(dq1);
        }else{
            insertRear(&res, dq2->arr[dq2->front]);
            deleteFront(dq2);
        }
    }
    Deque* new = &res;
    printf("===\n");
    displayDeque(new);
    printf("===\n");
    return new;
    
}

Deque* MergeSort(Deque* dq){
    
    if(dq == NULL){
        return dq;
        
    }
    if(dq->size < 2){
        return dq;
        
    }
    Deque split1;
    Deque split2;
    initializeDeque(&split1);
    initializeDeque(&split2);
    int tmp = dq->arr[dq->front];
    printf("tmp %d\n", tmp);
    for(int i = 0; i <= dq->size; i++){
        if(dq->arr[(dq->front + i) % MAX_SIZE] < tmp){
            printf("1\n");
            insertRear(&split1, dq->arr[(i + dq->front) % MAX_SIZE]);
            
        }else{
            printf("2\n");
            insertRear(&split2, dq->arr[(i + dq->front) % MAX_SIZE]);
        }
    }
    Deque* res;
    printf("----------\n");
    displayDeque(&split1);
    displayDeque(&split2);
    printf("----------\n");
    res = Merge(MergeSort(&split1), MergeSort(&split2));
    
    return res;
}

void BinarySearch(Deque* dq, int val){
    if(dq->size < 2){
        printf("элемент %d под индексом %d", val, 0);
    }
    int arr[dq->size];

    for(int i = 0; i < dq->size; i++){
        arr[i] = dq->arr[(dq->front + i) % MAX_SIZE];
    }

    bool found = false;
    int l = 0;
    int r = dq->size - 1;
    int m;

    while(l <= r){
        m = (l + r) / 2;
        if(val < arr[m]){
            r = m - 1;
        }else if(val > arr[m]){
            l = m + 1;
        }
        else{
            printf("индекс элемента - %d\n", m);
            return;
        }
    }
    printf("не нашел\n");
    
}



void Sort(Deque* deque) {
    if (deque->size > 0) {
        int n = deque->size;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                int current = (deque->front + j) % MAX_SIZE;
                int next = (deque->front + j + 1) % MAX_SIZE;

                if (deque->arr[current] > deque->arr[next]) {
                    // Swap elements
                    int temp = deque->arr[current];
                    deque->arr[current] = deque->arr[next];
                    deque->arr[next] = temp;
                }
            }
        }
    }
}




int main() {
    Deque deque;
    initializeDeque(&deque);

    int choice, value;
    int val;
    char tmp;

    do {
        printChoose();
        printf("Введите номер команды: ");
        scanf("%d", &choice);
        int random_size = 0;
        
        switch (choice) {
            case 1:
                random_size = rand() % 20 + 1;
                for (int i = 0; i < random_size; i++) {
                    value = rand() % 15;
                    insertFront(&deque, value);
                }
                printf("Рандомный дек создан.\n");
                break;
            case 2:
                displayDeque(&deque);
                break;
            case 3:
                if (scanf("%d%c", &val, &tmp) != 2 || (tmp != '\n'))
                {
                    printf("\ninvalid command\n");
                    while (getchar() != '\n'){};
                    break;
                }
                Sort(&deque);
                BinarySearch(&deque, val);
                break;
            case 4:
                printf("Введите значение для вставки в начало: ");
                scanf("%d", &value);
                insertFront(&deque, value);
                break;
            case 5:
                printf("Введите значение для вставки в конец: ");
                scanf("%d", &value);
                insertRear(&deque, value);
                break;
            case 6:
                deleteFront(&deque);
                break;
            case 7:
                deleteRear(&deque);
                break;
            case 8:
                Sort(&deque);
                printf("Дек отсортирован.\n");
                break;
            case 9:
                clearDeque(&deque);
                printf("Дек опустошен.\n");
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Ошибка! Несуществующее действие\n");
                break;
        }
    } while (choice != 0);

    return 0;
}