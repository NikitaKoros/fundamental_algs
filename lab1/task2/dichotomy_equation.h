#ifndef DIСHOTOMY_EQUATION_H
#define DIСHOTOMY_EQUATION_H

#include "util_task2.h"


typedef double (*FuncOfEquation)(double);

// double EEquation(double);
// double Ln2Equation(double);
// double Sqrt2Equation(double);
// double GammaEquation(double, double);

double CalculateUsingDichotomy(FuncOfEquation, double, double, double);
double DichotomyForCos(FuncOfEquation, double);
double DichotomyForGamma(double (*)(double, double), double, double, double);

#endif //DIСHOTOMY_EQUATION_H
