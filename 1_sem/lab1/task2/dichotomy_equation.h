#ifndef DICHOTOMY_EQUATION_H
#define DICHOTOMY_EQUATION_H

#include "util_task2.h"


typedef double (*FuncOfEquation)(double);

double CalculateUsingDichotomy(FuncOfEquation, double, double, double);
double DichotomyForCos(FuncOfEquation, double);
Error DichotomyForGamma(double (*)(double, double), double, double, double, double*);

#endif //DIСHOTOMY_EQUATION_H
