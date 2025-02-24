#ifndef TASK_8
#define TASK_8

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_BUFFER_SIZE 128

typedef enum {
    OK,
    OPEN_FILE_FAILURE,
    SAME_FILES_ERROR,
    WRONG_NUMBER_OF_PARAMETERS,
    INVALID_BASE,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR
} Error;

int isDigit(char);
int isAlpha(char);
int isAlNum(char);
int charToValue(char);
int findMinBase(const char*);
long long convertToDecimal(const char*, int);

const char *ErrorToString(Error);
void LogErrors(Error);

Error HandleInputOutput(char**, FILE**, FILE**);
bool MyStrcmp(char*, char*);
Error SameFiles(char*, char*);

#endif