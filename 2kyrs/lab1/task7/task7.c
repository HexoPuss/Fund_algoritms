#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

int process_g_flag(const char *file1, const char *file2, const char *output_file) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(output_file, "w");

    if (!f1 || !f2 || !out) {
        
        exit(EXIT_FAILURE);
    }

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    
    char *token1 = NULL, *token2 = NULL;
    int toggle = 1;
    printf("sDFF\n");

    while (1) {
        
        printf("sDFF\n");
        if (toggle && fgets(buffer1, BUFFER_SIZE, f1)) {
            token1 = strtok(buffer1, " \t\n");
            while (token1) {
                fprintf(out, "%s ", token1);
                token1 = strtok(NULL, " \t\n");
                toggle = !toggle;
            }
        }
        
        if (!toggle && fgets(buffer2, BUFFER_SIZE, f2)) {
            token2 = strtok(buffer2, " \t\n");
            while (token2) {
                fprintf(out, "%s ", token2);
                token2 = strtok(NULL, " \t\n");
                toggle = !toggle;
            }
        }
        
        if (feof(f1) && feof(f2)) {
            break;
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(out);
}

int process_a_flag(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");

    if (!in || !out) {
        
        return 1;
    }

    char buffer[BUFFER_SIZE];
    char *token = NULL;
    int count = 0;

    while (fgets(buffer, BUFFER_SIZE, in)) {
        token = strtok(buffer, " \t\n");
        
        while (token) {
            count++;
            char result[BUFFER_SIZE] = {0};
            
            if (count % 10 == 0) {
                for (int i = 0; i < strlen(token); i++) {
                    if (isupper(token[i])) {
                        token[i] = tolower(token[i]);
                    }
                }
                for (int i = 0; i < strlen(token); i++) {
                    char temp[10];
                    snprintf(temp, sizeof(temp), "%o", token[i]);
                    strcat(result, temp);
                }
            } else if (count % 2 == 0) {
                for (int i = 0; i < strlen(token); i++) {
                    if (islower(token[i])) {
                        token[i] = toupper(token[i]);
                    }
                }
                strcpy(result, token);
            } else if (count % 5 == 0) {
                for (int i = 0; i < strlen(token); i++) {
                    char temp[10];
                    snprintf(temp, sizeof(temp), "%c", token[i]);
                    strcat(result, temp);
                }
            } else {
                strcpy(result, token);
            }
            
            fprintf(out, "%s ", result);
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[]) {
    int outcome = 0;
    if (argc < 4) {
        fprintf(stderr, "Usage: %s -[g|a] file1 file2 output_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "/g") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Error: incorrect number of arguments for -g\n");
            return EXIT_FAILURE;
        }
        outcome = process_g_flag(argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: incorrect number of arguments for -a\n");
            return EXIT_FAILURE;
        }
        outcome = process_a_flag(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Error: unknown flag %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    if(outcome == 1){
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }
    return EXIT_SUCCESS;
}
