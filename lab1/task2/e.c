#include "util_task2.h"

double ELimit(double eps) {
	double cur = 0.0, prev = 0.0;
	int n = 1;

	do {
		prev = cur;
		cur = pow(1.0 + 1.0 / n, n);
		n++;
	} while (fabs(cur - prev) > eps);
	return cur;
}

double ESeries(double eps) {
	double res = 1.0;
	double nextMemb = 1.0;
	int n = 1;
	while (nextMemb > eps) {
		nextMemb /= n;
		res += nextMemb;
		n++;
	}
	return res;
}


