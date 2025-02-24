#include "util_task2.h"

int main() {
    Error err;
    
    double result;

    double exNum1 = 3.0, exNum2 = 2.5, exNum3 = 0.8, exNum4 = 124.056;
    int paramsCount = 4;
    err = GeomMean(&result, paramsCount, exNum1, exNum2, exNum3, exNum4);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    printf("Geometrical mean: %lf\n", result);

    int exponent = -2;
    double base = 2;

    err = MyPow(&result, base, exponent);
    if (err != OK) {

        LogErrors(err);
        return 1;
    }
    printf("Result of fast pow: %lf\n", result);
    return 0;
}