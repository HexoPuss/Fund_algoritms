#include <stdio.h>
#include <stdbool.h>


int main()
{
    int size;
    scanf("%d", &size);
    int mat[size][size];

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            scanf("%d", &mat[i][j]);
        }
    }

    int curi = size / 2 + size % 2 - 1;
    int curj = size / 2 + size % 2 - 1;

    int printcount = 1;

    int ver = 1;
    int hor = 1;
    int stepsize = 1;
    int step;
    bool breaking = false;
    printf("(%d, %d)\n", curi, curj);
    printf("%d ", mat[curi][curj]);

    while (printcount != size){
        step = 0;
        while(step < stepsize){
            step++;
            printf("%d ", mat[curi + step * ver][curj]);
            printcount++;
            
            if(printcount == size*size){
                breaking = true;
                printf("BREAK");
                break;
            }
        }

        if(breaking == true){break;}
        curi = curi + stepsize * ver;
        ver = ver * -1;

        step = 0;
        while(step < stepsize){
            step++;
            printf("%d ", mat[curi][curj + step * hor]);
            printcount++;
            if(printcount == size*size){
                breaking = true;
                printf("BREAK");
                break;
            }
        }

        if(breaking == true){break;}
        curj = curj + stepsize * hor;
        hor = hor * -1;
        

        stepsize++;
    }
    printf("END \nprints: %d\n", printcount);
}
