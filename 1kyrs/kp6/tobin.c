#include <stdio.h>
#include </home/octopussy/work/kp6/type.h>

int main(int argc, char* argv[])
{
    tab t;

    if (argc != 3){
        fprintf(stderr ,  "wrongargs");
        printf("%d", argc);
        return 1;
    }

    FILE*in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stderr, "wrong %s", argv[1]);
        return 2;
    }
    FILE*out = fopen(argv[2], "w");
    if (out == NULL){
        fprintf(stderr, "wrong %s", argv[2]);
        fclose(in);
        return 3;
    }

    while (fscanf(in, "%[^;];%d.%d.%d;%[^;];%d;%d;", t.shop, &t.date_d, &t.date_m, &t.date_y, t.name, &t.amount, &t.price) == 7){
        
        fwrite(&t, sizeof(tab), 1, out); //
        fprintf(stdout, "!");
        
        if(ferror(out)){
            fprintf(stderr, "ошибка чтения");
            fclose(in);
            fclose(out);
            return 5;
        }
    }
    
    if(ferror(in)){
        fprintf(stderr, "ошибка записи");
        fclose(in);
        fclose(out);
        return 5;
    }

    fclose(in);
    fclose(out);
    return 0;
}
