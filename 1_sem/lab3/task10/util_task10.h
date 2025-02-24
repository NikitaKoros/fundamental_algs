#ifndef TASK_10
#define TASK_10

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMS,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OPEN_FILE_FAILURE,
    SAME_FILES_ERROR,
} Error;

void LogErrors(Error);
const char *ErrorToString(const Error);

Error HandleInputOutput(char**, FILE**, FILE**);

bool MyStrcmp(char*, char*);
Error SameFiles(char*, char*);
#endif