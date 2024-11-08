#include "student.h"

Error ReadStudents(FILE* fileInput, Student** students, int* count) {
    Error err;
    int capacity = STUDENTS_CAPACITY;
    int index = 0;
    *students = malloc(capacity * sizeof(Student));
    if (students == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    *count = 0;
    while (true) {
        if (*count >= capacity) {
            capacity *= 2;
            Student* tmp = realloc(*students, capacity * sizeof(Student));
            if (tmp == NULL) {
                for (int i = 0; i < *count; i++) {
                    free((*students)[i].lastName);
                    free((*students)[i].firstName);
                }
                free(*students);
                return MEMORY_ALLOCATION_ERROR;
            }
            *students = tmp;
        }

        int id = 0;
        char* lastNameBuffer = NULL;
        char* firstNameBuffer = NULL;
        char* groupBuffer = NULL;
        unsigned char* gradesBuffer = NULL;


        err = ScanStudent(fileInput, &id, &firstNameBuffer, &lastNameBuffer, &groupBuffer, &gradesBuffer);
        if (err != OK && err != END_OF_FILE) {
            for (int i = 0; i < *count; i++) {
                free((*students)[i].lastName);
                free((*students)[i].firstName);
                free((*students)[i].group);
                free((*students)[i].grades);
            }
            free(*students);
            return err;
        }

        if (err == END_OF_FILE) {
            break;
        }

        (*students)[*count].id = id;
        (*students)[*count].lastName = lastNameBuffer;
        (*students)[*count].firstName = firstNameBuffer;
        (*students)[*count].group = groupBuffer;
        (*students)[*count].grades = gradesBuffer;

        (*count)++;
    }

    return OK;
}

Error ScanStudent(FILE* input, int* id, char** lastName, char** firstName, 
                    char** group, unsigned char** grades) {
    Error err;
    char c;
    char* curLastName = NULL;
    char* curFirstName = NULL;
    char* curGroup = NULL;
    unsigned char* curGrages = NULL;
    
    if (fscanf(input, "%d", id) != 1) { 
        if (feof(input)) {
            return END_OF_FILE;
        }   
        return STUDENT_INVALID_ID;
    }

    if (id < 0) {
        return STUDENT_INVALID_ID;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        return FILE_READ_ERROR;
    }

    err = ReadString(input, &curLastName);
    if (err != OK) {
        return err;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        free(curLastName);
        return FILE_READ_ERROR;
    }

    err = ReadString(input, &curFirstName);
    if (err != OK) {
        free(curLastName);
        return err;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        free(curLastName);
        free(curFirstName);
        return FILE_READ_ERROR;
    }

    err = ReadString(input, &curGroup);
    if (err != OK) {
        free(curLastName);
        free(curFirstName);
        return err;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        free(curLastName);
        free(curFirstName);
        free(curGroup);
        return FILE_READ_ERROR;
    }

    err = ReadGrades(input, &curGrages);
    if (err != OK) {
        free(curLastName);
        free(curFirstName);
        free(curGroup);
        return err;
    }
    
    *lastName = curLastName;
    *firstName = curFirstName;
    *group = curGroup;
    *grades = curGrages;
    return OK;
}

Error ReadString(FILE* fileInput, char** name) {
    int len = 0;
    int capacity = 10;
    char* curName = malloc(sizeof(char) * capacity);
    if (!curName) {
        return MEMORY_ALLOCATION_ERROR;
    }

    char c;
    while (isalpha(c = fgetc(fileInput))) {
        curName[len++] = c;
        if (len >= capacity) {
            capacity *= 2;
            char* newName = realloc(*name, capacity * sizeof(char));
            if (!newName) {
                free(curName);
                return MEMORY_ALLOCATION_ERROR;
            }
            curName = newName;
        }
    }

    ungetc(c, fileInput);

    if (len == 0) {
        free(curName);
        return STUDENT_INVALID_STRING;
    }

    curName[len] = '\0';
    *name = curName;
    return OK;
}

Error ReadGrades(FILE* fileInput, unsigned char** grades) {
    unsigned char* curGrades = malloc(sizeof(unsigned char) * EXAMS_AMOUNT);
    if (!curGrades) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < EXAMS_AMOUNT; i++) {
        if (fscanf(fileInput, "%hhu", &curGrades[i]) != 1) {
            free(curGrades);
            return STUDENT_INVALID_GRADES;
        }
    }

    *grades = curGrades;
    return OK;
}

Student *FindStudentById(Student *students, int count, unsigned int id) {
    for (int i = 0; i < count; ++i) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

Student *FindStudentByLastName(Student *students, int count, char *lastName) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

Student *FindStudentByFirstName(Student *students, int count, char *firstName) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].firstName, firstName) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

Student *FindStudentByGroup(Student *students, int count, char *group) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(students[i].group, group) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

int CompareByID(const void* first, const void* second) {
    Student* firstStudent = (Student*) first;
    Student* secondStudent = (Student*) second;

    return firstStudent->id - secondStudent->id;
}

int CompareByLastName(const void* first, const void* second) {
    Student* firstStudent = (Student*) first;
    Student* secondStudent = (Student*) second;

    return strcmp(firstStudent->lastName, secondStudent->lastName);
}

int CompareByFirstName(const void* first, const void* second) {
    Student* firstStudent = (Student*) first;
    Student* secondStudent = (Student*) second;

    return strcmp(firstStudent->firstName, secondStudent->firstName);
}

int CompareByGroup(const void* first, const void* second) {
    Student* firstStudent = (Student*) first;
    Student* secondStudent = (Student*) second;

    return strcmp(firstStudent->group, secondStudent->group);
}

void SortStudentsArray(Student* students, int count, Comparator comparator) {
    qsort(students, count, sizeof(Student), comparator);
}

void HandleTopStudents(FILE* output, Student* students, int count) {
    double average = 0.0;
    average = CalculateAllAverage(students, count);
    WriteTopStudents(output, students, count, average);
}

double CalculateAllAverage(Student* students, int count) {
    int sumGrades = 0;
    double curAvg = 0.0;
    double average = 0.0;
    Student student;
    for (int i = 0; i < count; i++) {
        student = students[i];
        curAvg = CalculateOneAverage(student);
        average += curAvg;
    }
    
    return average / count;
}

double CalculateOneAverage(Student student) {
    int sumGrades = 0;
    for (int k = 0; k < EXAMS_AMOUNT; k++) {
        sumGrades += student.grades[k];
    }

    return (double) sumGrades / EXAMS_AMOUNT;
}

void WriteTopStudents(FILE* output, Student* students, int count, double average) {
    double curAvg = 0.0;
    int amount = 0;
    Student student;
    fprintf(output, "\nStudents with grades above average:\n");
    for (int i = 0; i < count; i++) {
        student = students[i];
        curAvg = CalculateOneAverage(student);
        if (curAvg > average) {
            fprintf(output, "Name: %s; Surname: %s\n", 
                student.firstName, student.lastName);
            amount++;
        }
    }

    if (amount == 0) {
        fprintf(output, "There are no such students\n");
    }
    fprintf(output, "\n");    
}

void DeleteStudents(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        free(students[i].lastName);
        free(students[i].firstName);
        free(students[i].group);
        free(students[i].grades);
    }

    free(students);
}

