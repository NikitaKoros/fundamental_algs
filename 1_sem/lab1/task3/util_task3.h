#ifndef UTIL_TASK3_H
#define UTIL_TASK3_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include <ctype.h>

typedef enum {
  OK,
  WRONG_NUMBER_OF_PARAMETERS,
  INVALID_INPUT,
  INVALID_PRECISION,
  INVALID_SIDES_LENGTH,
  UNKNOWN_ERROR,
  INVALID_FLAG,
  ERROR_ATOF
} Error;

typedef enum {
  MODE_Q,
  MODE_M,
  MODE_T,
} WorkMode;

const char* ErrorToString(Error);
void ShowSpecification();
Error ReadFlag(const char*, WorkMode*);
Error MyAtof(const char*, double*);

int GetSetOfPermutations(double [6][3], double (*)[6][3], double);
int SolveQuadraticEquation(double, double, double, double, double*, double*);
void PrintRoots(int, const double*, const double*);
bool AreEqualPermutations(double[3], double[3], double);


bool CheckMultiples(int, int);

void PrintIfRightTriangle(bool);

Error CommandArgsHandler(int, char**, WorkMode*, double*);

Error ModeQHandler(const double *, double(*)[6][3], double*, int*);
Error ModeMHandler(const double*, int*, int*, bool*);
Error ModeTHandler(const double*, double*, double*, double*, bool*);

void PrintModeQ(Error, double*, double*, int);
void PrintModeM(Error, int, int, bool);
void PrintModeT(Error, double, double, double, bool);

#endif // UTIL_TASK3_H