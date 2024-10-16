#include <stdio.h>


int main(int argc, char* argv[])
{

    typedef struct
    {
        int ID;
        long long rating;
        char name[256];
        char author[64];
    } habropost;

    habropost t;

    

    if (argc != 2){
        fprint(stderr ,  'wrongargs');
        return 1;
    }

    FILE*in = fopen(argv[0], "r");
    if (in == NULL){
        fprintf(stderr, "wrong %s", argv[1]);
        return 2;
    }
    FILE*out = fopen(argv[1], "w");
    if (out == NULL){
        fprintf(stderr, "wrong %s", argv[2]);
        return 3;
    }


    fclose(in);
    fclose(out);
    return 0;
}
