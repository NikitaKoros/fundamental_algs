#ifndef TASK_2
#define TASK_2

#include <stdio.h>
#include <stdarg.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>

typedef enum {
    OK,
    INVALID_INPUT,
    TYPE_OVERFLOW,
} Error;

void LogErrors(Error);
const char *ErrorToString(const Error);

Error GeomMean(double*, int, ...);
Error MyPow(double*, double, int);

#endif