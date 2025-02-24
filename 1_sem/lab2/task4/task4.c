#include "util_task4.h"

int main(void) {
    double precision = 0.00001;
    /////////////////////////////////////////////////////////////////
    bool isConvex = false;
    Vertex v1 = {5.0, 3.0}, v2 = {6.0, 1.0}, v3 = {8.0, 3.0}, v4 = {6.0, 5.0},
           v5 = {4.0, 5.0}, v6 = {2.0, 3.0};
    isConvex = IsConvexPolygon(precision, 6, v1, v2, v3, v4, v5, v6);
    if (isConvex) {
        printf("Polygon is convex.\n\n");
    } else {
        printf("Polygon is not convex.\n\n");
    }
    /////////////////////////////////////////////////////////////////
    Error err = OK;
    double result = 0;
    // double a0 = 1.0, a1 = 2.0, a2 = 3.0, a3 = 4.0, a4 = 5.0, a5 = 6.0;
    // double x = 5000.0;
    // int coeffsNum = 6;
    double a0 = 5.0, a1 = 20.0, a2 = 18.0;
    double x = 13.0;
    int coeffsNum = 3;
    // err = CalculatePolynom(&result, x, coeffsNum, a0, a1, a2, a3, a4, a5);
    err = CalculatePolynom(&result, x, coeffsNum, a0, a1, a2);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    printf("Calculated Polynom: %lf\n\n", result);

    /////////////////////////////////////////////////////////////////
    bool* resultArr = NULL;
    int base = 10;
    int numsAmount = 6;
    err = FindKaprekarNumbers(&resultArr, base, numsAmount, "1", "34", "9", 
        "667", "999", "7778");
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    printf("Results: [");
    for (int i = 0; i < numsAmount; i++) {
        printf("%s", resultArr[i] ? "true" : "false");
        if (i != numsAmount - 1) {
            printf(", ");
        }
    }
    printf("]\n\n");
    free(resultArr);
    return 0;
}
