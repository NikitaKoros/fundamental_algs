#ifndef UTIL_TASK5_H
#define UTIL_TASK5_H
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include <ctype.h>

typedef enum {
    OK,
    INVALID_INPUT,
    WRONG_NUMBER_OF_PARAMS,
    TYPE_OVERFLOW,
    ERROR_ATOF
} Error;

typedef long double (*SeriesTypeFunc)(long double, long double, long double);

const char *ErrorToString(const Error);
int MyStrlen(const char *);
Error GetArgs(int, char**, long double*, long double*);
Error MyAtof(const char*, long double*);


long double ASeriesFunc(long double, long double, long double);
long double BSeriesFunc(long double, long double, long double);
long double CSeriesFunc(long double, long double, long double);
long double DSeriesFunc(long double, long double, long double);
Error RowCalc(SeriesTypeFunc, long double, long double, long double*, int, long double);


#endif