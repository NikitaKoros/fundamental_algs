#include "util_task2.h"



//#define M_PI 3.14159265358979323846L


// double GammaLimit(double eps) {
//     double cur = 1.0;
// 	double prev = 0.0;
// 	int m = 1;

// 	do {
// 		prev = cur;
// 		cur = 0.0;
//         long double factM = Factorial(m);

// 		for (int k = 1; k <= m; ++k) {
//             long double factK = Factorial(k);
// 			unsigned long long coeff = CombinationKM(k, m, factM, factK);
// 			double nextTerm = coeff * (pow(-1.0, k) / k) * logl(Factorial(k));
// 			cur += nextTerm;
// 		}

// 		m++;
// 	} while (fabs(cur - prev) > eps);

// 	return cur;


// }

Error GammaLimit(double precision, double* res) {
	double cur = 1.0;
	double prev = 0.0;
	int m = 1;

	do {
		prev = cur;
		cur = 0.0;

		for (int k = 1; k <= m; ++k) {
		    long long coeff = CombinationMK(m, k);
            if (coeff < 0.0) {
                *res = 0.0;
                return OWERFLOW_ERROR;
            }
			double term = coeff * (pow(-1.0, (k%2)) / k) * FactorialLog(k);
			cur += term;
		}

		m++;
	} while (fabs(cur - prev) > precision);

    *res = cur;
	return OK;
}

double GammaSeries(double eps) {

    double prevSum, curSum = 1.0;
    int k = 2;
    double nextTerm;
    do {
        prevSum = curSum;
        nextTerm = 1.0 /pow(floorl(sqrtl(k)), 2.0) - (1.0 / k);
        curSum += nextTerm;
        k++;
    } while (fabs(nextTerm) > eps);
    return (curSum - pow(M_PI, 2) / 6.0);
}

double CalculateLimitForGammaEq(double eps) {
    double n = 10.0 / eps;

    bool *primesArray = (bool*) malloc((n) * sizeof(bool));
    if (!primesArray) {
        exit(1);
    }

    GetPrimeNumbersArray(n, primesArray);
    double product = 1.0;
    for (int p = 2; p <= n; p++) {
        if (primesArray[p]) {
            product *= 1.0 - 1.0 / (double)p;
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
