#ifndef UTIL_TASK3_H
#define UTIL_TASK3_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
  OK,
  WRONG_NUMBER_OF_PARAMETERS,
  INVALID_INPUT,
  UNKNOWN_ERROR,
  INVALID_FLAG
} Error;

typedef enum {
  MODE_Q,
  MODE_M,
  MODE_T,
} WorkMode;

const char* ErrorToString(Error);
void ShowSpecification();
Error ReadFlag(const char*, WorkMode*);
double MyAtof(const char*);
int SolveQuadraticEcuation(double, double, double, double, double*, double*);
void PrintRoots(int, const double*, const double*);

#endif // UTIL_TASK3_H