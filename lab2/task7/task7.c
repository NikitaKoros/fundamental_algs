#include "util_task7.h"

double Func1(double x) {
    return pow(x - 1, 2) / (x - 1);
}

double Func2(double x) {
    return x * x - 3;
}

int main() {

    Error err;
    double result;
    double start = 0.0;
    double end = 2.0;
    double precision = 0.00000000000000000001;

    err = DichotomyEquation(&result, Func1, start, end, precision);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    printf("Result of the equation: %lf\n", result);

    err = DichotomyEquation(&result, Func2, start, end, precision);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    printf("Result of the equation: %lf\n", result);
    return 0;
}