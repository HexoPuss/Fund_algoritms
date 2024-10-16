#include <stdio.h>
#include </home/octopussy/work/kp6/type.h>
#include <string.h>


int main(int argc, char** argv)
{

    tab t;
    if (argc < 2 || argc > 4)
    {
        fprintf(stderr ,  "wrong amount of args");
        printf("%d", argc);
        return 1;
    }
    if ((argc == 3 || argc == 4) && ((strcmp(argv[1], "-sum") != 0) && (strcmp(argv[2], "-sum") != 0)))
    {
        fprintf(stderr, "invalid argument\n");
        return 3;
    }
    if(((strcmp(argv[1], "-av") != 0) && (strcmp(argv[2], "-av") != 0)) && argc == 4){
        fprintf(stderr, "invalid argument\n");
        return 3;
    }

    FILE*read = fopen(argv[argc - 1], "r");
    if (read == NULL){
        fprintf(stderr, "wrong %s", argv[argc]);
        return 2;
    }

    if(argc == 3 || argc == 4){
        if ((strcmp(argv[1], "-sum") == 0) || (strcmp(argv[1], "-sum") == 0)){
            int counter = 0;

            int y, m, d;
            int totalsum = 0;
            int yearsum[99];
            int monthsum[99][13];
            int daysum[99][13][32];
            int yearcount = 0;
            int monthcount = 0;


            while (fread(&t, sizeof(tab), 1, read) == 1){
                yearsum[t.date_y] += t.price * t.amount;
                monthsum[t.date_y][t.date_m] += t.price * t.amount;
                totalsum += t.price * t.amount;
                counter++;
            }
            int avarage = totalsum / counter;

            if(ferror(read)){
                fprintf(stderr, "ошибка чтения");
                fclose(read);
                return 5;
            }
            printf("\ntotalsum %d\n", totalsum);
            printf("по годам:\n");
            for(y = 0;y<99;y++){
                if(yearsum[y] != 0){
                    printf("за %d год: %d\n", y, yearsum[y]);
                }
            }
            printf("по месяцам:\n");
            for(y = 0;y<99;y++){
                for(m = 0;m<13;m++){
                    if (monthsum[y][m] != 0){
                        printf("за %d.%d: %d\n", m, y, monthsum[y][m]);
                    }
                }
            }
        

            if(argc == 4){
                int bolsheravno = 0;
                int menshe = 0;
                fseek(read, 0, SEEK_SET);
                while (fread(&t, sizeof(tab), 1, read) == 1){
                    if(t.amount*t.price >= avarage){
                        bolsheravno++;
                    }else{menshe++;}

                }
                printf("\nпродаж меньше среднего значения: %d\nбольше\n: %d", menshe, bolsheravno);
            }
        }
    }
    else
    {
        while (fread(&t, sizeof(tab), 1, read) == 1){ 
            printf("%s|%d.%d.%d|%s|%d по %d|\n", t.shop, t.date_d, t.date_m, t.date_y, t.name, t.amount, t.price);
        }
        if(ferror(read)){
            fprintf(stderr, "ошибка чтения");
            fclose(read);
            return 5;
        }
    }
    fclose(read);
}