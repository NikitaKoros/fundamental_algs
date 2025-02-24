#include "util_task5.h"

const char *ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case INVALID_INPUT:
            return "INVALID_INPUT";
		case TYPE_OVERFLOW:
			return "TYPE_OVERFLOW";
		case ERROR_ATOF:
			return "ERROR_ATOF";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

Error GetArgs(int argc, char** argv, long double* epsilon, long double* x) {
    if (argc != 3) {
		return WRONG_NUMBER_OF_PARAMS;
	}
	Error err = OK;
	err = MyAtof(argv[1], epsilon);
	if (err != OK) {
		return err;
	}
	err = MyAtof(argv[2], x);
	if (err != OK) {
		return err;
	}

	return OK;
}


Error MyAtof(const char* str, long double* arg) {
    long double result = 0.0;
    long double fraction = 0.0;
    int sign = 1;
    int decimalCount = 0;
    int maxDecimalPlaces = 17;
    //int intCount = 0;
    //int maxIntCount = 15;

    while (isspace(*str)) str++;

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    if (!isdigit(*str) && *str != '.') return ERROR_ATOF;

    while (isdigit(*str)) {
        int digit = *str - '0';
        if (sign == 1 && result > (LDBL_MAX - digit) / 10) return ERROR_ATOF;
        result = result * 10 + digit;
        //intCount++;
        str++;
    }

    if (*str == '.') {
        str++;
        while (isdigit(*str) && decimalCount < maxDecimalPlaces) {
            int digit = *str - '0';
            fraction = fraction * 10 + digit;
            decimalCount++;
            str++;
        }
        result += fraction / powl(10, decimalCount);
    }
    
    while(*str != '\0') {
        if (*str != '\0' && !isspace(*str) && !isdigit(*str)) return ERROR_ATOF;
        str++;
    }

    *arg = sign * result;

    if (fabsl(*arg) > LDBL_MAX) return ERROR_ATOF;

    return OK;
}

int MyStrlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

long double ASeriesFunc(long double n, const long double prev, long double x) {
    return prev * x / (n + 1.0);
}

long double BSeriesFunc(long double n, const long double prev, long double x) {
    return -prev * x * x / ((2.0 * n + 1.0) * (2.0 * n + 2.0));
}

long double CSeriesFunc(long double n, long double prev, long double x) {
    return prev * 27.0 * x * x * (n + 1.0) * (n + 1.0) * (n + 1.0) / 
    ((3.0 * n + 1.0) * (3.0 * n + 2.0) * (3.0 * n + 3.0));
}

long double DSeriesFunc(const long double n, long double prev, long double x) {
    return -prev * x * x * (2.0 * n + 1.0) / (2.0 * n + 2.0);
}


Error RowCalc(SeriesTypeFunc Func, long double precision, long double x, long double* output, int n, long double prevTerm) {
    long double prevSum, currentSum = prevTerm;
    Error err;

    do {
        long double term = Func(n, prevTerm, x);

        currentSum += term;
        prevTerm = term;
		if (n > 100000) {
			return TYPE_OVERFLOW;
		}

		if (currentSum > DBL_MAX || currentSum < -DBL_MAX) {
			return TYPE_OVERFLOW;
		}
        n++;
    //} while ((fabsl(currentSum) > precision) && (fabsl(prevSum - currentSum) > precision));
    } while (fabs(prevTerm) > precision);
    *output = currentSum;
    return OK;
}



				



