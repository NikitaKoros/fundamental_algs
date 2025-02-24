#include "util_task2.h"

double Ln2Limit(double eps) {
	double cur = 0.0, prev = 0.0;
	int n = 1;
	do {
		prev = cur;
		cur = n * (pow(2, 1.0 / n) - 1);
		n++;
	} while (fabs(cur - prev) > eps);

	return cur;
}

double Ln2Series(double eps) {
	double res = 0.0, nextMemb;
	int n = 1;
	int sign = 1;

	do {
		nextMemb = sign * (1.0 / n);
		res += nextMemb;
		sign = -sign;
		n++;
	} while (fabs(nextMemb) > eps);

	return res;
}
