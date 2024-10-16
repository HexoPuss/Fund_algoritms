#include <stdio.h>
#include "IterAndList.c"


void documentation(){
    printf("|| комманды:                                        ||\n");
    printf("|| i <index> <value> - добавление элемента в список ||\n");
    printf("|| r <index> - удаление елемента из списка          ||\n");
    printf("|| h - вывод документации                           ||\n");
    printf("|| p - печать списка                                ||\n");
    printf("|| t - развернуть список                            ||\n");
    printf("|| x - выход из программы                           ||\n");
    printf("\\\\==================================================//\n");
}


int main()
{
    documentation();
    list somel = create_list();
    list* l = &somel;
    int ind;
    char com, tmp, cmd;
    double val;
    iter it;
    
    while(true){
        printf("com: ");
        com = getchar();
        //while (com = ' '){com = getchar();}
        switch (com)
        {
            case 'h':
                if (getchar() != '\n') {
                    printf("\ninvalid command\n");
                    while(getchar() != '\n'){}
                    break;
                }
                documentation();
                break;
            
            case 'p':
                
                if (getchar() != '\n') {
                    printf("\ninvalid command\n");
                    while(getchar() != '\n'){};
                    break;
                }
                
                
                print_list(l);

                break;
            case 'i':

                if (scanf("%lf %d%c", &val, &ind, &tmp) != 3 || (tmp != '\n'))
                {
                    printf("\ninvalid command\n");
                    while (getchar() != '\n'){};
                    break;
                }
                it = begin_iter(l);
                
                for(int i = 0; i != ind; i++){
                    if(it.cur == NULL){
                        break;
                    }
                    it = iter_next(&it);
                }
                if(it.cur == NULL && !list_isempty(l)){
                    add_back(l, val);
                }else{
                    insert_before(&it, val);
                }
                break;
            
            case 'r':
                if (scanf("%d%c", &ind, &tmp) != 2 || (tmp != '\n'))
                {
                    printf("\ninvalid command\n");
                    while (getchar() != '\n'){};
                    break;
                }
                it = begin_iter(l);
                for(int i = 0; i < ind; i++){
                    if(it.cur == NULL){
                        break;
                    }
                    it = iter_next(&it);
                }
                printf("|%d|\n", it.cur == NULL);
                if(it.cur == NULL){
                    break;
                }
                remove_el(&it);
                break;

            case 't':
                if (getchar() != '\n') {
                    printf("\ninvalid command\n");
                    while(getchar() != '\n'){};
                    break;
                }
                if(l->first == NULL){
                    break;
                }
                list_task(l);
                printf("перевернутый список:\n");
                print_list(l);
                break;

            case 'x':
                if (getchar() != '\n') {
                    printf("Invalid command. Type 'h' for help\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("\nend of programm\n");
                destroy_list(l);
                return 0;

            default:
                printf("invalid commad\n");
                while(getchar() != '\n'){}
                break;
        }
    }
    
    destroy_list(l);
    return 0;
}