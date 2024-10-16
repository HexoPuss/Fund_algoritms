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
