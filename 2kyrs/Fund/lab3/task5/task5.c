#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    ID,
    NAME,
    SURENAME,
    GROUP
} Field;

typedef struct {
    unsigned int id;
    char *name;
    char *surname;
    char *group;
    unsigned int exams[5];
} Student;

void menu(){
    printf("\nМеню:\n");
    printf("2. Вывести список студентов\n");
    printf("3. Сортировать студентов\n");
    printf("4. Найти студентов\n");
    printf("5. Показать студентов с оценками выше средней\n");
    printf("6. Выводить в файл\n");
    printf("7. Выводить в консоль\n");
    printf("8. Выход\n");
    printf("Выберите действие: ");
}

void criterion_menu(){
    printf("1. ID\n");
    printf("2. Имя\n");
    printf("3. Фамилия\n");
    printf("4. Группа\n");
    printf("5. Назад\n");
    printf("Выберите: ");
}

void printStudent(Student stud, FILE* out){
    fprintf(out, "%u\t%s\t%s\t%s\t", stud.id, stud.surname, stud.name, stud.group);
    for(int j = 0; j < 5; j++) {
        fprintf(out, "%hhu ", stud.exams[j]);
    }
    fprintf(out, "\n");
}


int compareById(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return studentA->id - studentB->id;
}
int compareBySurname(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return strcmp(studentA->surname, studentB->surname);
}
int compareByName(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return strcmp(studentA->name, studentB->name);
}
int compareByGroup(const void* a, const void* b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return strcmp(studentA->group, studentB->group);
}

void sortStudents(Student *students, int count, int criterion) {
    switch(criterion) {
        case ID:
            qsort(students, count, sizeof(Student), compareById);
            break;
        case NAME:
            qsort(students, count, sizeof(Student), compareByName);
            break;
        case GROUP:
            qsort(students, count, sizeof(Student), compareByGroup);
            break;
        case SURENAME:
            qsort(students, count, sizeof(Student), compareBySurname);
            break;
        default:
            printf("Неверный критерий сортировки.\n");
    }
}


void findStudentsByGroup(Student *students, int count, char *group, FILE* out) {
    fprintf(out, "\nСтуденты из группы %s:\n", group);
    fprintf(out, "ID\tФамилия\tИмя\tГруппа\tОценки\n");
    for(int i = 0; i < count; i++) {
        if(strcmp(students[i].group, group) == 0) {
            printStudent(students[i], out);
        }
    }
}
void findStudentsByName(Student *students, int count, char *name, FILE* out) {
    fprintf(out, "\nСтуденты по имени %s:\n", name);
    fprintf(out, "ID\tФамилия\tИмя\tГруппа\tОценки\n");
    for(int i = 0; i < count; i++) {
        if(strcmp(students[i].name, name) == 0) {
            printStudent(students[i], out);
        }
    }
}
void findStudentsBySurname(Student *students, int count, char *surname, FILE* out) {
    fprintf(out, "\nСтуденты по фамилии %s:\n", surname);
    fprintf(out, "ID\tФамилия\tИмя\tГруппа\tОценки\n");
    for(int i = 0; i < count; i++) {
        if(strcmp(students[i].surname, surname) == 0) {
            printStudent(students[i], out);
        }
    }
}
void findStudentsById(Student *students, int count, unsigned int id, FILE* out) {
    fprintf(out, "\nСтуденты с id %u:\n", id);
    fprintf(out, "ID\tФамилия\tИмя\tГруппа\tОценки\n");
    for(int i = 0; i < count; i++) {
        if(students[i].id == id) {
            printStudent(students[i], out);
        }
    }
}


void printAboveAverageStudents(Student *students, int count, FILE* out) {
    if (count == 0) {
        fprintf(out, "Нет студентов для анализа.\n");
        return;
    }

    double total = 0.0;
    int totalexams = count * 5;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 5; j++) {
            total += students[i].exams[j];
        }
    }

    double overallAverage = total / totalexams;
    fprintf(out, "Общая средняя оценка: %.2f\n", overallAverage);


    int found = 0;
    fprintf(out, "\nСтуденты с оценками выше средней:\n");
    fprintf(out, "ID\tФамилия\tИмя\tГруппа\tОценки\tСредняя оценка\n");

    for (int i = 0; i < count; i++) {
        double studentTotal = 0.0;
        for (int j = 0; j < 5; j++) {
            studentTotal += students[i].exams[j];
        }
        double studentAverage = studentTotal / 5.0;

        if (studentAverage > overallAverage) {
            found = 1;
            printStudent(students[i], out);
        }
    }

    if (!found) {
        fprintf(out, "Нет студентов с оценками выше средней.\n");
    }
}


int ReadStudents(const char *filename, Student **students, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл %s.\n", filename);
        return -1;
    }
    int cap = 2;
    *count = 0;
    *students = malloc(cap * sizeof(Student));
    Student temp;
    int n;

    while (n = (fscanf(file, "%u %49s %49s %49s %u %u %u %u %u", &temp.id,  temp.name, temp.surname, temp.group, &temp.exams[0], &temp.exams[1], &temp.exams[2], &temp.exams[3], &temp.exams[4])) == 9)
    printf("N - %d", n);
    {
        if(*count == cap){
            
            
            Student *tempPtr = realloc(*students, (cap * 2) * sizeof(Student));
            if (!tempPtr) {
                printf("Ошибка выделения памяти.\n");
                free(*students);
                fclose(file);
                return -1;
            }
            *students = tempPtr;
        }
        
        (*students)[*count] = temp;
        (*count)++;
    }

    fclose(file);
    return 0;
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf( stderr, "Usage: %s <file_path> <trace_file>\n", argv[0]);
        return 1;
    }
    
    FILE* out = stdout;
    int choice, count, output_to_file = 0;
    Student* students = NULL;
    if (ReadStudents(argv[1], &students, &count) == 0) {
        printf("Студенты успешно загружены из файла %d\n", count);
    }
    if(count == 0 || students == NULL){
        fprintf(stderr, "студенты не считаны");
    }
    while(1) {
        menu();
        scanf("%d", &choice);


        switch(choice) {
            case 2:
                for(int i; i < count; i++){
                    printStudent(students[i], out);
                }
                break;
            case 3:
                fprintf(out, "Критерии сортировки:\n1. ID\n2. Фамилия\n3. Группа\nВыберите критерий: ");
                criterion_menu();
                int criterion;
                scanf("%d", &criterion);
                sortStudents(students, count, criterion);
                printf("Студенты отсортированы.\n");
                break;
            case 4:
                unsigned int id;
                char* crit;
                printf("\nПо какому критерию будет производится поиск?:\n");
                
                scanf("%d", &choice);
                if (choice == 5){
                    break;
                }
                if(choice > 0 && choice < 5){
                    printf("Введите критерий: ");
                    if (choice == 1){
                        scanf("%u", &id);
                    }else{
                        scanf("%s", crit);
                    }
                }
                switch (choice)
                {
                case 1:
                    findStudentsById(students, count, id, out);
                    break;
                case 2:
                    findStudentsByName(students, count, crit, out);
                    break;
                case 3:
                    findStudentsBySurname(students, count, crit, out);
                    break;
                case 4:
                    findStudentsByGroup(students, count, crit, out);
                    break;
                default:
                    printf("некорректный ввод\n");
                    break;
                }
                break;
            case 5:
                printAboveAverageStudents(students, count, out);
                break;
            case 6:
                output_to_file = 1;
                break;
            case 7:
                output_to_file = 0;
                break;
            case 8:
                for (int i = 0; i < count; i++) {
                    free(students[i].name);
                    free(students[i].surname);
                    free(students[i].group);
                }
                free(students);
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        if(output_to_file){
            out = fopen(argv[2], "w");
            if(!out){
                fprintf(stderr, "ошибка открытия файла");
                return 1;
            }
        }
    }
    
    for (int i = 0; i < count; i++) {
        free(students[i].name);
        free(students[i].surname);
        free(students[i].group);
    }
    free(students);

    return 0;
}
