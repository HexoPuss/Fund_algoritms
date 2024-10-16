#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Key 
{
    long int key1;
    char key2[5];
    int to;
} Key;

typedef struct Data 
{
    char data [50];
} Data;



void Create_Table (FILE* file, Key* keys, Data* datas) 
{
    for (int i = 0; i < 20; i++) 
    {
        fscanf (file, "%s %[^\n]\n", keys [i].key2, datas [i].data);
        keys [i].to = i;
    }
}

void Print_Table (const Key* keys, const Data* datas) 
{
    printf ("|---------------------------------------------------------|\n");
    printf ("|   Ключ   |                   Строка                     |\n");
    printf ("|---------------------------------------------------------|\n");
    for (int i = 0; i < 20; i++) 
    { 
        printf ("   %s   |%s\n", keys [i].key2, datas [keys [i].to].data);
        printf ("|---------------------------------------------------------|\n");
    }
}

void Reverse (Key* keys) 
{
    for (int i = 0; i < 10; i++) 
    {
        Key reverse;
        reverse = keys [i];
        keys [i] = keys [19 - i];
        keys [19 - i] = reverse;
        
    }
}



int keycmp (Key keya, Key keyb) 
{
    
    if (strcmp(keya.key2, keyb.key2) > 0){
        return 1;
    }if (strcmp(keya.key2, keyb.key2) < 0){
        return -1;
    }
    return 0;
}


void Lin_sort_with_counting (Key* keys) 
{
    
    int i, j;
    int count[20];
    for(i = 0; i < 20; i++){count[i] = 0;}
    
    for (i = 0; i < 20; i++) 
    {
        for (j = i + 1; j < 20; j++){
            if(keycmp(keys[i], keys[j]) == -1){
                count[j]++;
            }else{
                count[i]++;
            }
        }
    }
    Key new_keys[20];

    for(int k = 0; k < 20; k++){
        new_keys[count[k]] = keys[k];
    }
    for(i = 0; i < 20; i++){
        keys[i] = new_keys[i];
    }
    
}

void Binary_Search (Key* keys, Data* datas) 
{
    printf ("Введите значение ключа, по которому будет происходить поиск.\n");
    Key search;
    scanf ("%s", search.key2);
    printf("%s\n", search.key2);
    int L = 0, R = 19, found = 0, m;
    while (L <= R && found == 0) 
    {
        m = (L + R) / 2;
        printf("%d\n", m);
        if (keycmp (keys [m], search) == 1) R = m - 1;
        else if (keycmp (search, keys [m]) == 1) L = m + 1;
        else
        { 
            found = 1;
        }
    }
    if (found) 
    {
        printf ("%s\n",datas [keys [m].to].data);
    }
    else printf ("Строки с таким ключом не найдено\n");
}

int Sorted (Key* keys) 
{
    for (int i = 0; i < 19; i++) 
    {
        if (keycmp (keys [i + 1], keys [i]) == -1) return 0;
    }
    return 1;
}

int Reverse_Sorted (Key* keys) 
{
    for (int i = 19; i > 0; i--) 
    {
        if (keycmp (keys [i - 1], keys [i]) == -1) return 0;
    }
    return 1;
}

void Shuffle (Key* keys) 
{
    for (int i = 0; i < 20; i++) 
    {
        int a = rand () % 20, b = rand () % 20;
        Key temp = keys [a];
        keys [a] = keys [b];
        keys [b] = temp;
    }
}

void Print_Menu ()
{
    printf ("\nВыберите действие:\n1) Создать таблицу.\n2) Произвести сортировку (линейная с подсчетом))\n3) Бинарный поиск по ключу (только с отсортированной таблицей).\n4) Распечатать таблицу.\n5) Реверс таблицы.\n6) Перемешать таблицу.\n0) Выйти\nДействие: ");
}
 
int main (void)
{
    
    Key keys [20];
    Data datas [20];
    int action;
    FILE* file = fopen ("table", "r");
    
    do 
    {
        Print_Menu ();
        
        scanf ("%d", &action);
        
        if (action == 0) break;
        switch (action)
        {
            case 1:
                
                Create_Table (file, keys, datas);
                break;
            case 2: 
                
                Lin_sort_with_counting (keys);
                break;
            case 3:
                Binary_Search (keys, datas);
                break;
            case 4:
                Print_Table (keys, datas);
                break;
            case 5:
                Reverse (keys);
                break;
            case 6:
                Shuffle (keys);
                break;
            case 0:
                action = 0;
            default:
                printf ("\nНет такого действия\n");
                break;
        }
    } while (action);
    fclose (file);
}

 


    
