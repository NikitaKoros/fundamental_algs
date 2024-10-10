#ifndef UTIL_TASK2_H
#define UTIL_TASK2_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


typedef enum { OK, WRONG_NUMBER_OF_PARAMS, INVALID_INPUT } Error;

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

double GammaLimit(double);
double GammaSeries(double);
double GammaEquation(double, double);

double Factorial(int);
double CombinationKM(int, int);
void GetPrimeNumbersArray(int, bool*);
double CalculateLimitForGammaEq(double);

#endif // UTIL_TASK2_H
