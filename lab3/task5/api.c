#include "api.h"

Error InteractiveDialogue(Student* students, int count, FILE* output) {
    
    Error err;
    int command;
    Student* student = NULL;
    // if (!student) {
    //     DeleteStudents(students, count);
    //     return MEMORY_ALLOCATION_ERROR;
    // }
    
    Comparator comparators[4] = {
        CompareByID,
        CompareByLastName,
        CompareByFirstName,
        CompareByGroup
    };

    while (true) {
        ShowMenu();
        scanf ("%d", &command);
        switch (command) {
        case 1:
            unsigned int id = RequestId();
            student = FindStudentById(students, count, id);
            if (student == NULL) {
                printf("Student not found!\n");
                break;
            }
            double average = CalculateOneAverage(*student);
            PrintStudent(student);
            PrintStudentToFile(student, average, output);
            break;
        case 2:
            char* lastName = RequestLastName();
            student = FindStudentByLastName(students, count, lastName);
            free(lastName);
            PrintStudent(student);
            break;
        case 3:
            char* firstName = RequestFirstName();
            student = FindStudentByFirstName(students, count, firstName);
            free(firstName);
            PrintStudent(student);
            break;
        case 4:
            char* group = RequestGroup();
            student = FindStudentByGroup(students, count, group);
            free(group);
            PrintStudent(student);
            break;
        case 5:
            students = HandleSorting(students, count, comparators);
            PrintSortedStudents(students, count);
            break;
        case 6:
            HandleTopStudents(output, students, count);
            break;
        case 7:
            //free(student);
            return OK;
        default:
            break;
        }
    }
    
    return OK;
}

void ShowMenu() {
    printf("\nPossible commands:\n");
    printf("1. Search by ID\n");
    printf("2. Search by last name\n");
    printf("3. Search by first name\n");
    printf("4. Search by group\n");
    printf("5. Sorting\n");
    printf("6. Show students with grades above average\n");
    printf("7. Exit\n\n");
}

unsigned int RequestId() {
    printf("Please enter student's ID:\n");
    int id;
    if (scanf("%d", &id) != 1) {
        return -1;
    }

    if (id < 0) {
        return -1;
    }

    return (unsigned int) id;
}

char* RequestLastName() {
    printf("Please enter student's last name:\n");
    char* lastName = NULL;
    if (scanf("%ms", &lastName) != 1) {
        return NULL;
    }

    return lastName;
}

char* RequestFirstName() {
    printf("Please enter student's first name:\n");
    char* firstName = NULL;
    if (scanf("%ms", &firstName) != 1) {
        return NULL;
    }

    return firstName;
}

char* RequestGroup() {
    printf("Please enter student's group:\n");
    char* group = NULL;
    if (scanf("%ms", &group) != 1) {
        return NULL;
    }

    return group;
}

int ChooseSortType() {
    int type;
    if (scanf("%d", &type) != 1) {
        return -1;
    }

    if (type < 1 || type > 4) {
        return -1;
    }

    return type;
}

Student* HandleSorting(Student* students, int count, Comparator* comparators) {
    
    int type;
    while(true) {
        printf("Enter sorting type 1 - 4:\n");
        type = ChooseSortType();
        if (type != -1) {
            break;
        }
    }

    Comparator cmp = comparators[type - 1];
    ////////////////////
    for (int i = 0; i < count; i++) {
    printf("Student %d: %s %s\n", students[i].id, students[i].firstName, students[i].lastName);
}
    SortStudentsArray(students, count, cmp);

    return students;
}

void PrintSortedStudents(Student* students, int count) {
    printf("Sorted students:\n");
    for (int i = 0; i < count; i++) {
        int id = students[i].id;
        char* lastName = students[i].lastName;
        char* firstName = students[i].firstName;
        char* group = students[i].group;
        printf("%d;%s;%s;%s\n", id, firstName, lastName, group);
    }
    printf("\n");
}

void PrintStudentToFile(Student* student, double average, FILE* output) {
    if (student == NULL) {
        fprintf(output, "Student not found!\n");
        return;
    }
    
    fprintf(output, "Name: %s, Surname: %s, Group: %s, Avg grade: %lf\n\n", 
        student->firstName, student->lastName, student->group, average);
}

void PrintStudent(Student* student) {
    if (student == NULL) {
        printf("Student not found!\n");
        return;
    }
    
    printf("Name: %s, Surname: %s, Group: %s\n\n", 
        student->firstName, student->lastName, student->group);
}





