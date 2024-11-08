#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "util_task3.h"
#include <string.h>

#define EMPLOYEES_CAPACITY 10
#define MAX_NAME_LENGTH 50

typedef struct {
    unsigned int id;
    char* firstName;
    char* lastName;
    double salary;
} Employee;

typedef int (*Comparator) (const void*, const void*);

Error ReadEmployees(FILE*, Employee** , int*);
Error ScanEmployee(FILE*, int*, char**, char**, double*);

int desComparison(const void *, const void*);
int ascComparison(const void *, const void*);
Error SortEmployees(Employee*, int, Comparator, FILE*);

void PrintEmployees(Employee*, int, FILE*);

void DeleteEmployees(Employee*, int);

#endif