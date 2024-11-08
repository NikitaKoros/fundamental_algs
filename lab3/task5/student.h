#ifndef STUDENT_H
#define STUDENT_H

#include "util_task5.h"

typedef struct {
    unsigned int id;
    char* firstName;
    char* lastName;
    char* group;
    unsigned char* grades;
} Student;

#define EXAMS_AMOUNT 10
#define STUDENTS_CAPACITY 20

Error ReadStudents(FILE*, Student**, int*);
Error ScanStudent(FILE*, int*, char**, char**, char**, unsigned char**);
Error ReadString(FILE*, char**);
Error ReadGrades(FILE*, unsigned char**);
void DeleteStudents(Student*, int);

Student *FindStudentById(Student*, int, unsigned int);
Student *FindStudentByLastName(Student*, int, char *);
Student *FindStudentByFirstName(Student*, int, char *);
Student *FindStudentByGroup(Student*, int, char *);

void SortStudentsArray(Student*, int, Comparator);
int CompareByID(const void*, const void*);
int CompareByLastName(const void*, const void*);
int CompareByFirstName(const void*, const void*); 
int CompareByGroup(const void*, const void*);

void HandleTopStudents(FILE*, Student*, int);
double CalculateAllAverage(Student*, int);
double CalculateOneAverage(Student);
void WriteTopStudents(FILE*, Student*, int, double);


#endif