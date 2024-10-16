#include <stdio.h>
#include "IterAndList.c"


void main()
{
    
    list l = create_list();
    list* newl = &l;
    iter it = begin_iter(newl);
    iter* newit = &it;
    list_el* b = malloc(sizeof(list_el));
    list_el* a = malloc(sizeof(list_el));
    list_el* c;
    
    insert_before(newit, 4);
    it = end_iter(newl);
    newit = &it;
    insert_before(newit, 5);


    it = end_iter(newl);
    it = iter_next(&it);
    newit = &it;
    
    add_back(newl, 6);

    it = begin_iter(newl);
    it = iter_next(&it);
    it = iter_next(&it);

    remove_el(&it);

    printf("%d\n", newit->cur == NULL);
    print_list(&l);
}

