#include "employee.h"

Error ReadEmployees(FILE* fileInput, Employee** employees, int* count) {
    Error err;
    int capacity = EMPLOYEES_CAPACITY;
    int index = 0;
    *employees = malloc(capacity * sizeof(Employee));
    if (employees == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    *count = 0;
    while (true) {
        if (*count >= capacity) {
            capacity *= 2;
            Employee* tmp = realloc(*employees, capacity * sizeof(Employee));
            if (tmp == NULL) {
                for (int i = 0; i < *count; i++) {
                    free((*employees)[i].firstName);
                    free((*employees)[i].lastName);
                }
                free(*employees);
                return MEMORY_ALLOCATION_ERROR;
            }
            *employees = tmp;
        }

        int id = 0;
        char* firstNameBuffer = NULL;
        char* lastNameBuffer = NULL;
        double salary = 0;

        err = ScanEmployee(fileInput, &id, &firstNameBuffer, &lastNameBuffer, &salary);
        if (err != OK && err != END_OF_FILE) {
            for (int i = 0; i < *count; i++) {
                free((*employees)[i].firstName);
                free((*employees)[i].lastName);
            }
            free(*employees);
            return err;
        }

        if (err == END_OF_FILE) {
            break;
        }

        (*employees)[*count].id = id;
        (*employees)[*count].firstName = firstNameBuffer;
        (*employees)[*count].lastName = lastNameBuffer;
        (*employees)[*count].salary = salary;

        (*count)++;
    }

    return OK;
}

Error ScanEmployee(FILE* input, int* id, char** firstName, char** lastName, double* salary) {
    Error err;
    char c;
    char* curFirstName = NULL;
    char* curLastName = NULL;
    
    if (fscanf(input, "%d", id) != 1) { 
        if (feof(input)) {
            return END_OF_FILE;
        }   
        return EMPLY_INVALID_ID;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        return FILE_READ_ERROR;
    }

    err = ReadName(input, &curFirstName);
    if (err != OK) {
        return err;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        free(curFirstName);
        printf("%s %c\n", curFirstName, c);
        return FILE_READ_ERROR;
    }

    err = ReadName(input, &curLastName);
    if (err != OK) {
        free(curFirstName);
        return err;
    }

    c = getc(input);
    if (isalpha(c) || isdigit(c)) {
        free(curFirstName);
        free(curLastName);
        return FILE_READ_ERROR;
    }

    if (fscanf(input, "%lf", salary) != 1) {
        free(curFirstName);
        free(curLastName);
        return EMPLY_INVALID_SALARY;
    }
    
    *firstName = curFirstName;
    *lastName = curLastName;
    return OK;
}

void DeleteEmployees(Employee* employees, int count) {
    for (int i = 0; i < count; i++) {
        free(employees[i].firstName);
        free(employees[i].lastName);
    }
    free(employees);
}

int desComparison(const void * firstEmployee, const void* secondEmployee) {
    const Employee* f = (const Employee*) firstEmployee;
    const Employee* s = (const Employee*) secondEmployee;

    if (f->salary != s->salary) {
        if (f->salary < s->salary) {
            return 1;
        }
        return -1;
    }

    int cmp;
    if ((cmp = strcmp(f->lastName, s->lastName)) != 0) {
        return cmp;
    }

    if (cmp = strcmp(f->firstName, s->lastName) != 0) {
        return cmp;
    }

    return f->id < s->id;
}

int ascComparison(const void * firstEmployee, const void* secondEmployee) {
    const Employee* f = (const Employee*) firstEmployee;
    const Employee* s = (const Employee*) secondEmployee;

    if (f->salary != s->salary) {
        if (f->salary > s->salary) return 1;
        return -1;
    }

    int cmp;
    if ((cmp = strcmp(f->lastName, s->lastName)) != 0) {
        return -cmp;
    }
    
    cmp = strcmp(f->firstName, s->firstName);
    if ((cmp = strcmp(f->firstName, s->firstName)) != 0) {
        return -cmp;
    }

    return f->id > s->id;
}

Error SortEmployees(Employee* employees, int count, Comparator comparator, FILE* fileOutput) {
    qsort(employees, count, sizeof(Employee), comparator);

    return OK;
}

void PrintEmployees(Employee* employees, int employeeAmount, FILE* fileOutput) {
    Employee emp;
    int id;
    char* firstName;
    char* lastName;
    double salary;
    
    for (int index = 0; index < employeeAmount; index++) {
        emp = employees[index];
        id = emp.id;
        firstName = emp.firstName;
        lastName = emp.lastName;
        salary = emp.salary;
        fprintf(fileOutput, "%d. %d;%s;%s;%lf\n", 
            index + 1, id, firstName, lastName, salary);
    }

    fprintf(fileOutput, "\n##############################\n\n");
}