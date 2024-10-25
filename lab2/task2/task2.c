#include "util_task2.h"

int main() {
    Error err;
    
    double result;

    double exNum1 = 3.0, exNum2 = 2.5, exNum3 = 0.81, exNum4 = 124.056;
    int paramsCount = 4;
    err = GeomMean(&result, paramsCount, exNum1, exNum2, exNum3, exNum4);
    if (err != OK) {
        printf("err1\n");
        LogErrors(err);
        return 1;
    }
    printf("Geometrical mean: %lf\n", result);

    int exponent = 3;
    double base = 20;

    err = MyPow(&result, base, exponent);
    if (err != OK) {
        printf("err2\n");

        LogErrors(err);
        return 1;
    }
    printf("Result of fast pow: %lf\n", result);
    return 0;
}