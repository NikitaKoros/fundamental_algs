#include "util_task9.h"

int main() {
    Error err;

    //int base = 4;
    //double fraction1 = 0.1, fraction2 = 0.2, fraction3 = 0.01, fraction4 = 0.02, fraction5 = 0.023;
    //int paramsCount = 5;
    int base = 3;
    double fraction1 = 0.0, fraction2 = 1.0 / 3.0, fraction3 = 1.0 / 9.0;
    int paramsCount = 3;
    bool* resultsArr = malloc (sizeof(bool) * paramsCount);
    
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
    return 0;
}