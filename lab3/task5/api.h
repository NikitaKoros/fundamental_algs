#ifndef API_H
#define API_H

#include "util_task5.h"
#include "student.h"

Error InteractiveDialogue(Student*, int, FILE*);
void ShowMenu();
unsigned int RequestId();
const char* RequestLastName();
const char* RequestFirstName();
const char* RequestGroup();
int ChooseSortType();
Student* HandleSorting(Student*, int, Comparator*);

void PrintSortedStudents(Student*, int);
void PrintStudentToFile(Student*, double, FILE*);
void PrintStudent(Student*);

#endif