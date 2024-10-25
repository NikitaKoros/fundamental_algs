#ifndef TASK_9
#define TASK_9

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    OK,
    INVALID_INPUT,
    WRONG_FRACTION,
    TYPE_OVERFLOW,
    MEMORY_ALLOCATION_ERROR,
} Error;

void LogErrors(Error);
const char *ErrorToString(const Error);

Error ProcessFractions(bool**, int, int, ...);
Error HasRepresentationInBase(bool*, int, int, int);
int gcd(int, int);

#endif