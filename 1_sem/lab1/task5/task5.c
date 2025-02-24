#include "util_task5.h"

int main(int argc, char** argv) {
    
	long double precision = 0.0;
	long double x = 0.0;
	Error err = GetArgs(argc, argv, &precision, &x);
	if (err != OK) {
		fprintf(stderr, "Error when parsing params: %s\n", ErrorToString(err));
		return err;
	}
	if (precision <= 0.0) {
		printf("Precision can't be equal or less than 0.0\n");
		return 0;
	}
	if (x == 0.0) {
		printf("x must not be 0.0\n");
		return 0;
	}
	long double result = 0.0;
	SeriesTypeFunc rowsFuncsArr[4] = {ASeriesFunc, BSeriesFunc, CSeriesFunc, DSeriesFunc};
	int startsArr[4] = {0, 0, 0, 1};
	long double firstElemsArr[4] = {1.0, 1.0, 1.0, -x * x * 0.5};
	printf("Calculating Rows, precision = %.10Lf, x = %.10Lf\n", precision, x);
	for (int i = 0; i < 4; i++) {
		err = RowCalc(rowsFuncsArr[i], precision, x, &result, startsArr[i], firstElemsArr[i]);
		if (err != OK) {
			fprintf(stderr, "Error during calculation %c row: %s. Row diverges.\n", 'A' + i, ErrorToString(err));
			continue;
		}
		printf("Result of sum %c: %.10Lf\n", 'A' + i, result);
	}
	return 0;
}
