#ifndef TASK_3
#define TASK_3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


typedef enum {
    OK,
    END_OF_FILE,
    INVALID_INPUT,
    WRONG_NUMBER_OF_PARAMS,
    INVALID_FLAG,
    OPEN_FILE_ERROR,
    SAME_FILES_ERROR,
    FILE_READ_ERROR,
    MEMORY_ALLOCATION_ERROR,
    EMPLY_INVALID_ID,
    EMPLY_INVALID_NAME,
    EMPLY_INVALID_SALARY,
} Error;

typedef enum {
    FLAG_A,
    FLAG_D,
} Flag;

void LogErrors(Error);
const char *ErrorToString(const Error);

Error ProcessArgs(int, char**, char**, char**, Flag*);
Error ReadFlag(const char*, Flag*);
Error ReadName(FILE*, char**);

Error HandleInputOutput(char*, char*, FILE**, FILE**);
bool MyStrcmp(char*, char*);
Error SameFiles(char*, char*);

#endif