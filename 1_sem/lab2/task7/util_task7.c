#include "util_task7.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case TOO_MUCH_ITERATIONS:
            return "TOO_MUCH_ITERATIONS";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        case INVALID_BOUNDS:
            return "INVALID_BOUNDS";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error DichotomyEquation(double* result, EquatFunc Func, double start, double end, double precision) {
    
    double mid = (start + end) / 2;
    int n = 0;

    if (Func(start) * Func(end) >= 0) {
        return INVALID_BOUNDS;
    }

    while(fabs(start - end) / 2 > precision) {
        if (n > MAX_ITERATIONS) {
            return TOO_MUCH_ITERATIONS;
        }

        mid = (start + end) / 2;

        if (Func(start) * Func(mid) >= 0) {
            start = mid;
        } else {
            end = mid;
        }

        n++;
    }

    *result = mid;
    return OK;
}