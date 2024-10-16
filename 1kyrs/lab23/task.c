#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"



void documentation(){
    printf("|| комманды:                                      ||\n");
    printf("|| a <value> - добавление элемента в дерево       ||\n");
    printf("|| r <value> - удаление елемента из дерева        ||\n");
    printf("|| h - вывод документации                         ||\n");
    printf("|| p - печать дерева                              ||\n");
    printf("|| t - подсчет нетерминальных вершин              ||\n");
    printf("|| x - выход из программы                         ||\n");
    printf("\\\\================================================//\n");
}


int main()
{
    documentation();
    tree t = create_tree();
    char com, tmp;
    double val;
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
                if(t != NULL){
                    print_tree(t, 0);
                }else{printf("\ntree is empty\n");}

                break;
            case 'a':

                if (scanf("%lf%c", &val, &tmp) != 2 || (tmp != '\n'))
                {
                    printf("\ninvalid command\n");
                    while (getchar() != '\n'){};
                    break;
                }
                insert(&t, val);
                break;
            
            case 'r':
                if (scanf("%lf%c", &val, &tmp) != 2 || (tmp != '\n'))
                {
                    printf("\ninvalid command\n");
                    while (getchar() != '\n'){};
                    break;
                }
                t = node_remove(t, val);
                break;

            case 't':
                if (getchar() != '\n') {
                    printf("\ninvalid command\n");
                    while(getchar() != '\n'){};
                    break;
                }
                printf("кол - во нетерминальных вершин - %d\n", count_task(t));
                break;

//            case 'c':
//                if (getchar() != '\n') {
//                    printf("\ninvalid command\n");
//                    while(getchar() != '\n'){};
//                    break;
//                }
//                clear_tree(t);
//                tree t = create_tree();
//                break;
//
            case 'e':
                if (getchar() != '\n') {
                    printf("\ninvalid command\n");
                    while(getchar() != '\n'){};
                    break;
                }
            case 'x':
                if (getchar() != '\n') {
                    printf("Invalid command. Type 'h' for help\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("\nend of programm\n");
                clear_tree(t);
                return 0;

            default:
                printf("invalid commad\n");
                while(getchar() != '\n'){}
                break;
        }
    }
    
    clear_tree(t);
    return 0;
}