#include "util_task2.h"

double GammaLimit(double eps) {

    double prev, cur = 1.0;
    int m = 1;

    do {
        prev = cur;
        cur = 0.0;

        for (int k = 1; k <= m; k++) {
            long double binomCoeff = CombinationKM(k, m);
            double nextTerm = binomCoeff * (pow(-1.0, k) / k) * log(Factorial(k));
            cur += nextTerm;
        }

        m++;
    } while (fabs(cur - prev) > eps);

    return cur;
}

double GammaSeries(double eps) {

    double prevSum, curSum = 1.0;
    int k = 2;
    double nextTerm;
    do {
        prevSum = curSum;
        nextTerm = 1.0 /pow(floor(sqrt(k)), 2) - (1.0 / k);
        curSum += nextTerm;
        k++;
    } while (fabs(nextTerm) > eps);
    return (curSum - pow(M_PI, 2) / 6.0);
}

double CalculateLimitForGammaEq(double eps) {
    double n = 10 / eps;

    bool *primesArray = (bool*) malloc((n + 1) * sizeof(bool));
    if (!primesArray) {
        exit(1);
    }

    GetPrimeNumbersArray(n, primesArray);
    double product = 1.0;
    for (int p = 2; p <= n; p++) {
        if (primesArray[p]) {
            product *= 1.0 - 1.0 / p;
        }
    }

    free(primesArray);

    return log(n) * product;
}

void GetPrimeNumbersArray(int n, bool* array) {
    for (int i = 0; i <= n; i++) {
        array[i] = true;
    }
    array[0] = array[1] = false;
    for (int p = 2; p * p <= n; p++) {
        if (array[p]) {
            for (int i = p * p; i <= n; i += p) {
                array[i] = false;
            }
        }
    }
}
