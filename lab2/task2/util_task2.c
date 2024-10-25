#include "util_task2.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error GeomMean(double* result, int paramsCount, ...) {
    
    if (paramsCount < 1) {
        return INVALID_INPUT;
    }
    
    double value = 1.0;
    va_list args;
    va_start(args, paramsCount);
    double dlbMin = DBL_MIN;
    for (int i = 0; i < paramsCount; i++) {
        double number = va_arg(args, double);
        if (isnan(number) || isinf(number) || number < 0.0 || fabs(number) < DBL_MIN) {
            va_end(args);
            return INVALID_INPUT;
        }

        value *= pow(number, 1.0 / paramsCount);
		if (value > DBL_MAX || value < -DBL_MAX || isnan(value)) {
            va_end(args);
			return TYPE_OVERFLOW;
		}

    }

    va_end(args);

    *result = value;
    return OK;
}

Error MyPow(double* result, double base, int exponent) {
    Error err;

    if (exponent == 0) {
        *result = 1.0;
        return OK;
    }

    if (exponent < 0) {
        err = MyPow(result, 1 / base, -exponent);
        //*result = 1.0 / *result;
        if (*result > DBL_MAX || *result < -DBL_MAX || isnan(*result)) {
		    return TYPE_OVERFLOW;
	    }
        return err;
    }

    double halfValue;
    err = MyPow(&halfValue, base, exponent / 2);
    if (err != OK) {
        return err;
    }

    if (halfValue > DBL_MAX || halfValue < -DBL_MAX || isnan(halfValue)) {
		return TYPE_OVERFLOW;
	}

    *result = halfValue * halfValue;

    if ((exponent % 2) != 0) {
        *result *= base;
        if (*result > DBL_MAX || *result < -DBL_MAX || isnan(*result)) {
		    return TYPE_OVERFLOW;
	    }
    }

    return OK;
}