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


int keycmp (Key keya, Key keyb) 
{
    
    return strcmp(keya.key2, keyb.key2);
    
}


void main(){
    Key keys[20];
    Key a, b;
    
    scanf("%s %s", a.key2, b.key2);
    printf("%s, %s\n", a.key2, b.key2);
    keys[4] = a;
    printf("%s", keys[4].key2);

}