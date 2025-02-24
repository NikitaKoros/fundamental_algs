#include "integrals.h"

double IntegralA(double x) {
    return log(1 + x) / x;
}

double IntegralB(double x) {
    return exp(-pow(x, 2) / 2);
}

double IntegralC(double x) {
    if (x >= 1.0) {
        return 0.0;
    }
    
    return -log(1 - x);
}

double IntegralD(double x) {
    return pow(x, x);
}

Error IntegrateWithRectangles(int steps, FuncOfIntegral func, double* result) {
    if (steps <= 0) {
        return INVALID_INPUT;
    }
    double step = 1.0 / steps;
    double value = 0.0;
    for (int i = 1; i <= steps; i++) {
        double current = func(i * step);
        if (isinf(current) || isnan(current)) {
            return TYPE_OVERFLOW;
        }
        value += current;
    }
    *result = value * step;
    return OK;
}

Error Integrate(double precision, FuncOfIntegral func, double* output) {
    int steps = 10;
    Error err;
    double cur = 0.0, prev = 0.0;
    do {
        prev = cur;
        err = IntegrateWithRectangles(steps, func, &cur);
        if (err != OK) {
            return err;
        }
        steps *= 2;
    } while (fabs(cur - prev) > precision);

    *output = cur;
    return OK;
}