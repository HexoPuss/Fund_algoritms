#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef enum CASES{
    CASE_L,
    CASE_R,
    CASE_U,
    CASE_N,
    CASE_C,
} CASES;

int CheckFlag(const char* kflag, char valid_flag) {
	return (kflag[0] == '-' || kflag[0] == '/') && (kflag[1] == valid_flag) && (kflag[2] == '\0');
}

int GetOpts(int argc, char** argv, CASES* option) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <flag> <input>\n", argv[0]);
		return 1;
	}

	char flags[5] = {'l', 'r', 'u', 'n', 'c'};

	for (int i = 0; i < 5; i++) {
		if (CheckFlag(argv[1], flags[i])) {
			*option = i;
			return 0;
		}
	}

	return 3;
}

int my_atoi(const char *str, int* num) {
    int result = 0;
    int sign = 1;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (1) {
        if(isdigit(*str)){
            int digit = *str - '0';

            result = result * 10 + digit;
            str++;
        }else if(*str != '\0'){
            return 1;
        }else{
            break;
        }
    }

    *num = sign * result;
    return 0;
}

size_t my_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

char *reverse_string(const char *str) {
    size_t len = my_strlen(str);
    char *reversed = (char *)malloc((len + 1) * sizeof(char));
    if (!reversed) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        reversed[i] = str[len - i - 1];
    }
    reversed[len] = '\0';
    return reversed;
}

char *uppercase_odd(const char *str) {
    size_t len = my_strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (!result) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        result[i] = (i % 2 == 1) ? toupper(str[i]) : str[i];
    }
    result[len] = '\0';
    return result;
}

char *sort_characters(const char *str) {
    size_t len = my_strlen(str);
    char *sorted = (char *)malloc((len + 1) * sizeof(char));
    if (!sorted) return NULL;
    
    int digits_count = 0, letters_count = 0, others_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (isdigit(str[i])) digits_count++;
        else if (isalpha(str[i])) letters_count++;
        else others_count++;
    }
    
    size_t di = 0, li = digits_count, oi = digits_count + letters_count;
    
    for (size_t i = 0; i < len; i++) {
        if (isdigit(str[i])) sorted[di++] = str[i];
        else if (isalpha(str[i])) sorted[li++] = str[i];
        else sorted[oi++] = str[i];
    }
    sorted[len] = '\0';
    return sorted;
}

void shuffle(char *str, unsigned int seed) {
    size_t len = my_strlen(str);
    srand(seed);
    for (size_t i = len - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char *concatenate_random(int argc, char *argv[], unsigned int seed) {
    char* temp = argv[2];
    argv[2] = argv[3];
    argv[3] = temp;

    int total_len = 0;

    for (int i = 3; i < argc; i++) {
        total_len += my_strlen(argv[i]);
    }
    char *concat = (char *)malloc((total_len + 1) * sizeof(char));
    if (!concat) return NULL;
    
    int j, step = 0;
    for (int i = 3; i < argc; i++) {
        char *current = argv[i];
        for(j = 0; current[j] != '\0';j++) {
            concat[step++] = current[j];
            
        }
    }
    
    concat[total_len] = '\0';
    
    shuffle(concat, seed);
    return concat;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <flag> <string> [<number> <strings>...]\n", argv[0]);
        return 1;
    }
    CASES opt;
	int res = GetOpts(argc, argv, &opt);
	switch (res) {
		case 0:
			break;
		case 1:
			printf("Incorrect number of arguments.\n");
			return 1;
		case 3:
			printf("Unknown flag: %s\n", argv[1]);
			return 1;
		default:
			printf("Unknown error.\n");
			return 1;
	}
    char flag = argv[1][1];
    switch (opt)
    {
    case 0:
        printf("Length: %zu\n", my_strlen(argv[2]));
        break;
    case 1:
        char *reversed = reverse_string(argv[2]);
        if (reversed) {
            printf("Reversed: %s\n", reversed);
            free(reversed);
        }
        break;
    case 2:
        char *uppercased = uppercase_odd(argv[2]);
        if (uppercased) {
            printf("Uppercased: %s\n", uppercased);
            free(uppercased);
        }
        break;
    case 3:
        char *sorted = sort_characters(argv[2]);
        if (sorted) {
            printf("Sorted: %s\n", sorted);
            free(sorted);
        }
        break;
    case 4:
        if (argc < 4) {
            fprintf(stderr, "Usage for -c flag: %s -s <string> <seed> <...>\n", argv[0]);
            return 1;
        }
        int tmp;
        if(my_atoi(argv[3], &tmp)){
            fprintf(stderr, "my_atoi Errror");
            return 1;
        }
        unsigned int seed = (unsigned int) tmp;
        char *concatenated = concatenate_random(argc, argv, seed);
        if (concatenated) {
            printf("Randomized Concatenation: %s\n", concatenated);
            free(concatenated);
        }
        break;
    default:
        fprintf(stderr, "Unknown flag: %c\n", flag);
        return 1;
        break;
    }
    
    return 0;
}