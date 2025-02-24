#ifndef UTIL_TASK6_H
#define UTIL_TASK6_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <ctype.h>

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMETERS,
    TYPE_OVERFLOW,
    INVALID_INPUT,
    ERROR_ATOF,
    SERIES_DIVERGES
} Error;



const char *ErrorToString(const Error error);
void ShowSpecification();
Error ReadPrecision(char*, double*);
void LogErrors(Error);
Error MyAtof(const char*, double*);


#endif //UTIL_TASK6_H