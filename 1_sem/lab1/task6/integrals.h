#ifndef INTEGRALS_H
#define INTEGRALS_H
#include "util_task6.h"

typedef double (*FuncOfIntegral)(double);
Error IntegrateWithRectangles(int, FuncOfIntegral, double*);
Error Integrate(double, FuncOfIntegral, double*);



double IntegralA(double);
double IntegralB(double);
double IntegralC(double);
double IntegralD(double);

#endif