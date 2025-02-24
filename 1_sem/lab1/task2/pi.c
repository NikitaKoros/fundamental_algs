#include "util_task2.h"

double PiLimit(double eps) {
	double cur = 4.0, prev = 0.0;
	int n = 1;
	do {
		prev = cur;
		cur *= (4 * n * (n + 1)) / pow(2 * n + 1, 2);
		n++;
	} while (fabs(cur - prev) > eps);
	return cur;
}

double PiSeries(double eps) {
	double res = 0.0, nextMemb;
	int n = 1;
	int sign = 1;
	do {
		nextMemb = sign * (1.0 / (2 * n - 1));
		res += nextMemb;
		sign = -sign;
		n++;
	} while (fabs(nextMemb) > eps);

	return res * 4.0;
}
