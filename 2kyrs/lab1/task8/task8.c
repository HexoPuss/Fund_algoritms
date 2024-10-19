#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 1024

int base_value(char c) {
    if (isdigit(c))
        return c - '0';
    else if (isalpha(c))
        return tolower(c) - 'a' + 10;
    else
        return -1;
}

int detect_min_base(const char *number) {
    int min_base = 2;
    for (int i = 0; number[i]; i++) {
        int val = base_value(number[i]);
        if (val >= min_base)
            min_base = val + 1;
    }
    return min_base <= 36 ? min_base : -1;
}

long convert_to_decimal(const char *number, int base) {
    long decimal = 0;
    while (*number) {
        int val = base_value(*number);
        if (val >= base)
            return -1; // Invalid number for the given base
        decimal = decimal * base + val;
        number++;
    }
    return decimal;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Unable to open input file");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("Unable to open output file");
        fclose(input_file);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (fscanf(input_file, "%1023s", buffer) == 1) {
        int min_base = detect_min_base(buffer);
        long decimal = convert_to_decimal(buffer, min_base);
        
        if (decimal == -1) {
            fprintf(stderr, "Invalid number format for %s\n", buffer);
            continue;
        }

        fprintf(output_file, "%s (base %d) = %ld (base 10)\n", buffer, min_base, decimal);
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
