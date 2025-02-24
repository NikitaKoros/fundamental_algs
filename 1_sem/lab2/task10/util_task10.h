#ifndef TASK10
#define TASK10

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    OK,
    TYPE_OVERFLOW,
    MEMORY_ALLOCATION_ERROR,
} Error;

const char* ErrorToString(const Error);
void LogErrors(Error);

void CompareResults(double *, double *, int, double, double);
Error DecomposePolynom(double **, double, double, int, ...);
Error GetDerivative(double *, int, double, int, const double *);

#endif