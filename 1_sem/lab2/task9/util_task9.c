#include "util_task9.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        case WRONG_FRACTION:
            return "WRONG_FRACTION";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error ProcessFractions(bool** resultsArr, int base, int paramsCount, ...) {
    Error err;

    if (paramsCount < 1) {
        return INVALID_INPUT;
    }

    *resultsArr = malloc (sizeof(bool) * paramsCount);
    if (*resultsArr == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    va_list args;
    va_start(args, paramsCount);

    for (int i = 0; i < paramsCount; i++) {
        double numerator = va_arg(args, double);
        if (numerator >= 1.0) {
            free(*resultsArr);
            va_end(args);
            return INVALID_INPUT;
        }
        double denominator = 1.0;

        while (numerator != floor(numerator)) {
            numerator *= 10;
            denominator *= 10;
        }

        bool ans;

        err = HasRepresentationInBase(&ans, numerator, denominator, base);
        if (err != OK) {
            free(*resultsArr);
            va_end(args);
            return err;
        }

        (*resultsArr)[i] = ans;
    }
    va_end(args);
    
    return OK;
}

Error HasRepresentationInBase(bool* res, int numerator, int denominator, int base) {
    if (denominator == 0 || base == 0) {

        return INVALID_INPUT;
    }

    if (numerator == 0) {
        *res = true;                 //???
        return OK;
    }

    int divisor = gcd(numerator, denominator);
    if (divisor == 1) {
        *res = false;
        return OK;
    }

    numerator /= divisor;
    denominator /= divisor;

    while (denominator % base == 0)
        denominator /= base;

    for (int i = 2; i <= base; i++) {
        if (base % i == 0) {
            while (denominator % i == 0) {
                denominator /= i;
            }   
        }
    }

    if (denominator == 1) {
        *res = true;
        return OK;
    } else {
        *res = false;
        return OK;
    }
}

int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
