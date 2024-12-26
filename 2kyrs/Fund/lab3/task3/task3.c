#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char firstName[50];
    char lastName[50];
    double salary;
} Employee;

int ReadEmployees(FILE *f, Employee **employees, int *size) {

	*size = 0;
	int cap = 10;
	*employees = (Employee *)malloc(sizeof(Employee) * cap);

	if (!*employees) {
		fclose(f);
		return 2;
	}

	int n;

	while ((n = fscanf(f, "%u %s %s %lf", &((*employees)[*size].id), (*employees)[*size].firstName,
	                   (*employees)[*size].lastName, &((*employees)[*size].salary))) > 0) {

		if (n != 4) {
			return 3;
		}

		(*size)++;
		if (*size == cap) {
			Employee *tmp = (Employee *)realloc(*employees, sizeof(Employee) * cap * 2);
			cap *= 2;
			if (!tmp) {
				free(employees);
				return 4;
			}
			*employees = tmp;
		}
	}
	if(!feof(f)) return 5;
    
	return 0;
}

int compare_a(const void *a, const void *b) {
    const Employee *empA = (const Employee *)a;
    const Employee *empB = (const Employee *)b;
    
    
    int salaryCompare;
    if (empA->salary < empB->salary)
        salaryCompare = -1;
    else if (empA->salary > empB->salary)
        salaryCompare = 1;
    else
        salaryCompare = 0;
    
    if (salaryCompare == 0) {
        int lastNameCompare = strcmp(empA->lastName, empB->lastName);
        if (lastNameCompare == 0) {
            int firstNameCompare = strcmp(empA->firstName, empB->firstName);
            if (firstNameCompare == 0) {
                return empA->id - empB->id;
            }
            return firstNameCompare;
        }
        return lastNameCompare;
    }
    
    return salaryCompare;
}

int compare_d(const void *a, const void *b) {
    const Employee *empA = (const Employee *)a;
    const Employee *empB = (const Employee *)b;
    
    
    int salaryCompare;
    if (empA->salary < empB->salary)
        salaryCompare = -1;
    else if (empA->salary > empB->salary)
        salaryCompare = 1;
    else
        salaryCompare = 0;
    
    if (salaryCompare == 0) {
        int lastNameCompare = strcmp(empA->lastName, empB->lastName);
        if (lastNameCompare == 0) {
            int firstNameCompare = strcmp(empA->firstName, empB->firstName);
            if (firstNameCompare == 0) {
                return -(empA->id - empB->id);
            }
            return -firstNameCompare;
        }
        return -lastNameCompare;
    }
    
    return -salaryCompare;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <-a/-d> <output_file>\n", argv[0]);
        return 1;
    }
    
    char *inputFilePath = argv[1];
    char *outputFilePath = argv[3];
    if((argv[2][0] != '/' && argv[2][0] != '-') || (strlen(argv[2]) != 2)){
        fprintf(stderr, "invalid flag, %c\n", argv[2][0]);
        return 1;
    }
    char flag = argv[2][1];
    fprintf(stdout, "flag, %c\n", flag);
    
    
    FILE *inputFile = fopen(inputFilePath, "r");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    Employee* employees;
    int count = 0;
    
    if(ReadEmployees(inputFile, &employees, &count) != 0){
        fprintf(stderr, "Error reading input file");
    }
    
    fclose(inputFile);
    
    if(flag == 'a'){
        qsort(employees, count, sizeof(Employee), compare_a);
    }else if(flag == 'd'){
        printf("SFDSDF\n");
        qsort(employees, count, sizeof(Employee), compare_d);
    }else{
        fprintf(stderr, "Error invalid flag");
    }
    
    FILE *outputFile = fopen(outputFilePath, "w");
    if (!outputFile) {
        perror("Error opening output file");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        fprintf(outputFile, "%d %s %s %.2f\n", employees[i].id, employees[i].firstName,
                employees[i].lastName, employees[i].salary);
    }
    for(int i = 0; i < count; i++){
        free(employees[i].firstName);
        free(employees[i].lastName);
    }
    free(employees);
    fclose(outputFile);
    return 0;
}