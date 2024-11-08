#ifndef TASK_1
#define TASK_1

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_ARGS,
    MEMORY_ALLOCATION_ERROR
} Error;

void LogErrors(Error);
const char *ErrorToString(const Error);

Error ReadInput(int*, unsigned int*);

Error DecimalToBinBase(int, unsigned int, char**);
int BitwiseIncrement(int);
int BitwiseDecrement(int);
int BitwiseNegative(int);

void ReverseString(char*, int, int);

#endif