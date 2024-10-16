#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct list_el list_el;

struct list_el
{
    double val;
    list_el* next;
    list_el* prev;
};



typedef struct
{
    list_el* first;
    list_el* last;
    
}list;

typedef struct 
{
    list_el* cur;
    list* l;
}iter;

//list_el* zero;

list create_list(){
    list l;
    l.first = NULL;
    l.last = NULL;
    return l;
}

void destroy_list(list* l){
    list_el* cur = l->first;
    list_el* tmp;
    while (cur != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    l->first = NULL;
    l->last = NULL;
}

iter begin_iter(list* l){
    iter it;
    it.cur = l->first;
    it.l = l;
    return it;
}

iter end_iter(list* l){
    iter it;
    it.cur = l->last;
    it.l = l;
    return it;
}

double val(iter* it){
    return it->cur->val;
}

bool list_isempty(list* l){
    return(l->first == NULL);
}

iter iter_next(iter* it){
    iter new;
    new.cur = it->cur->next;
    new.l = it->l;
    return new;
}

bool iter_eq(iter* it1, iter* it2){
    return (it1 ==  it2)&&(it1->cur == it2->cur);
}

void print_list(list* l){
    iter it;
    iter end = end_iter(l);
    for(it = begin_iter(l); it.cur != NULL; it = iter_next(&it)){
        printf("%lf\n", it.cur->val);
    }
}

void insert_before(iter* it, double val){
    list_el* el = malloc(sizeof(list_el));
    if(el == NULL){return;}
    
    el->val = val;
    el->next = NULL;
    el->prev = NULL;

    if(it->l->first == NULL && it->l->last == NULL){
        it->l->first = el;
        it->l->last = el;
    }else if(it->cur == it->l->first){
        el->next = it->cur;
        it->cur->prev = el;
        it->l->first = el;
    }else if (it->cur == it->l->last->next)
    {
        el->next = it->cur;
        it->cur->prev = el;
        it->l->last = el;
    }else{
        el->prev = it->cur->prev;
        el->next = it->cur;
        it->cur->prev->next = el;
        it->cur->prev = el;
    }
    return;
}

/*void add_front(list* l, double val){
    iter it = begin_iter(l);
    insert_before(&it, val);
}*/

void add_back(list* l, double val){
    iter ite = end_iter(l);
    iter* it = &ite;

    list_el* el = malloc(sizeof(list_el));
    if(el == NULL){return;}
    el->val = val;
    el->next = NULL;

    el->prev = it->cur;
    it->cur->next = el;
    it->l->last = el;

}

void remove_el(iter* it){
    list_el* todel = it->cur;
    if(todel->prev != NULL){
        it->cur->prev->next = todel->next;
    }else{
        it->l->first = todel->next;
    }
    if(todel->next != NULL){
        it->cur->next->prev = todel->prev;
    }else{
        it->l->last = todel->prev;
    }

    free(todel);
}
list list_task(list* l){
    list_el* el = l->first;
    list_el* newlast = el;
    list_el* tmp;

    while (true){
        tmp = el->next;
        el->next = el->prev;
        el->prev = tmp;

        if(tmp == NULL){
            l->first = el;
            break;
        }
        el = tmp;
    }
    l->last = newlast;
}

