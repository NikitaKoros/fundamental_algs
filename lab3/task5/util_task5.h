#ifndef UTIL_TASK_2
#define UTIL_TASK_2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    OK,
    INVALID_INPUT,
    FILE_OPEN_ERROR,
    FILE_READ_ERROR,
    FILE_SAME_ERROR,
    MEMORY_ALLOCATION_ERROR,
    WRONG_NUMBER_OF_PARAMS,
    STUDENT_INVALID_ID,
    STUDENT_INVALID_STRING,
    STUDENT_INVALID_GRADES,
    END_OF_FILE,
} Error;

typedef int (*Comparator) (const void*, const void*);

void LogErrors(Error);
const char *ErrorToString(const Error);

Error HandleInputOutput(char**, FILE**, FILE**);
Error SameFiles(char*, char*);
bool MyStrcmp(char*, char*);

#endif