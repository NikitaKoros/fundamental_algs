#ifndef UTIL_TASK2_H
#define UTIL_TASK2_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef enum { OK, WRONG_NUMBER_OF_PARAMS, INVALID_INPUT, OWERFLOW_ERROR, TOO_HIGH_PRECISION} Error;

void ShowSpecification();
const char *ErrorToString(const Error);

Error StringToDouble(char *, double *);

double ELimit(double);
double ESeries(double);
double EEquation(double);

double PiLimit(double);
double PiSeries(double);
double PiEquation(double);

double Ln2Limit(double);
double Ln2Series(double);
double Ln2Equation(double);

double Sqrt2Limit(double);
double Sqrt2Series(double);
double Sqrt2Equation(double);

Error GammaLimit(double, double*);
double GammaSeries(double);
double GammaEquation(double, double);

double FactorialLog(int);
long long CombinationMK(int, int);
void GetPrimeNumbersArray(int, bool*);
double CalculateLimitForGammaEq(double);

#endif // UTIL_TASK2_H
