#include "dichotomy_equation.h"

double EEquation(double x) {
	return log(x) - 1;
}

double PiEquation(double x) {
    return cos(x) + 1;
}

double Ln2Equation(double x) {
	return exp(x) - 2;
}

double Sqrt2Equation(double x) {
	return x * x - 2;
}

double GammaEquation(double x, double precision) {
    double limit = CalculateLimitForGammaEq(precision);
    return exp(-x) - limit;
}

double CalculateUsingDichotomy(FuncOfEquation Func, double high, double low, double eps) {
	double mid;

	while ((high - low)/2 > eps){
		mid = (high + low) / 2.0;

		if ((Func(mid) * Func(low)) < 0) {
			high = mid;
		} else {
			low = mid;
		}
	}

	return (high + low) / 2.0;
}

double DichotomyForCos(FuncOfEquation Func, double eps) {
	double curMid, nextMid1, nextMid2;
	double high = 6.0, low = 0.0;
	while ((high - low) / 2 > eps) {
		curMid = (high + low) / 2;
		nextMid1 = (low + curMid) / 2;
		nextMid2 = (high + curMid) / 2;

		if (fabs(Func(nextMid1)) < fabs(Func(nextMid2))) {
			high = curMid;
		} else {
			low = curMid;
		}
	}

	return curMid;
}

double DichotomyForGamma(double (*Func)(double, double), double high, double low, double eps) {
    double mid;

    while ((high - low) > eps) {
        mid = (low + high) / 2.0;

        if (Func(mid, eps) == 0.0) {
            return mid;
        } else if (Func(mid, eps) * Func(low, eps) < 0) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return mid;
}