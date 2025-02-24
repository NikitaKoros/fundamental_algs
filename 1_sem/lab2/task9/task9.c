#include "util_task9.h"

int main() {
    Error err;

    int base = 3;
    double fraction1 = 0.023, fraction2 = 0.5, fraction3 = 0.04, fraction4 = 0.02, fraction5 = 0.125;
    int paramsCount = 5;
    // int base = 3;
    // double fraction1 = 0.0, fraction2 = 0.4, fraction3 = 0.5;
    // int paramsCount = 3;
    bool* resultsArr;
    
    //err = ProcessFractions(&resultsArr, base, paramsCount, fraction1, fraction2, fraction3, fraction4, fraction5);
    err = ProcessFractions(&resultsArr, base, paramsCount, fraction1, fraction2, fraction3);

    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    printf("Has finite representation in given base: ");
    for (int i = 0; i < paramsCount; i++) {
        printf("%d.%s ", i, resultsArr[i] ? "true" : "false");
    }
    printf("\n");
    free(resultsArr);
    return 0;
}