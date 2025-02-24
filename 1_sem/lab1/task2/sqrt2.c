#include "util_task2.h"

double Sqrt2Limit(double eps) {
	double cur = -0.5, prev;
	do {
		prev = cur;
		cur = prev - 0.5 * pow(prev, 2) + 1;
	} while (fabs(cur - prev) > eps);

	return cur;
}

double Sqrt2Series(double eps) {
	double res = 1.0, nextMemb;
	int k = 2;
	do {
		nextMemb = pow(2, pow(2, -k));
		res *= nextMemb;
		k++;
	} while (fabs(nextMemb - 1) > eps);     //или можно сравнивать pow(2, -k)

	return res;
}
