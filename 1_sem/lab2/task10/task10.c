#include "util_task10.h"

int main() {
    
    Error err = OK;
    double givenCoeffs[5] = {-2.0, 1.0, -3.0, 0.0, 1.0};
    int n = 4;
    double precision = 0.00001;
    double a = 3.0;
    
    double* resultCoeffs = NULL;
    
    err = DecomposePolynom(&resultCoeffs, precision, a, n, -2.0, 1.0, -3.0, 0.0, 1.0);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    printf("Result coefficients in decomposed function: ");
    for (int i = 0; i <= n; i++) {
        printf("g%d = %f ", i, resultCoeffs[i]);
    }
    printf("\n\n");
    CompareResults(givenCoeffs, resultCoeffs, n, 5, a);

    free(resultCoeffs);
    return 0;
}