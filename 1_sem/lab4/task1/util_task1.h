#ifndef TASK_1
#define TASK_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define INITIAL_LINE_LENGTH 64

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMS,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OPEN_FILE_FAILURE,
    FILE_PROCESSING_FAILED,
    END_OF_FILE,
} Error;

void LogErrors(Error);
const char *ErrorToString(const Error);

Error HandleInputOutput(char *, FILE **);
Error ReadLine(FILE*, char**);

char *strndup(const char *, size_t);
size_t strnlen(const char *, size_t);
char *strdup(const char *);

int NextPrime(int n);
int isPrime(int num);
int GetNewTableSize(int currentSize);

#endif