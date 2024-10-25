#ifndef TASK_7
#define TASK_7

#include <stdio.h>
#include <math.h>

#define MAX_ITERATIONS 100000
typedef enum {
    OK,
    INVALID_INPUT,
    INVALID_BOUNDS,
    TYPE_OVERFLOW,
    TOO_MUCH_ITERATIONS
} Error;

typedef double (*EquatFunc)(double);
Error DichotomyEquation(double*, EquatFunc, double, double, double);

void LogErrors(Error);
const char *ErrorToString(const Error);

#endif