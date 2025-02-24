#include "util_task10.h"

const char *ErrorToString(const Error error) {
    switch (error) {
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occurred: %s\n", ErrorToString(err));
}

Error GetDerivative(double *res, int i, double a, int n, const double *coeffs) {
    double result = 0.0;

    for (int j = i; j <= n; j++) {
        double term = coeffs[j];
        for (int k = 0; k < i; k++) {
            term *= (j - k);
            if (isinf(term) || isnan(term)) {
                return TYPE_OVERFLOW;
            }
        }
        double power = pow(a, j - i);
        if (isinf(power) || isnan(power)) {
            return TYPE_OVERFLOW;
        }

        result += term * power;
        if (isinf(result) || isnan(result)) {
            return TYPE_OVERFLOW;
        }
    }

    *res = result;
    return OK;
}

Error DecomposePolynom(double **result, double epsilon, double a, int n, ...) {
    double *resultCoeffs = (double *)malloc((n + 1) * sizeof(double));
    if (!resultCoeffs) {
        return MEMORY_ALLOCATION_ERROR;
    }

    va_list args;
    va_start(args, n);

    double *givenCoeffs = (double *)malloc((n + 1) * sizeof(double));
    if (!givenCoeffs) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i <= n; i++) {
        givenCoeffs[i] = va_arg(args, double);
    }
    va_end(args);

    Error err = OK;
    double factorial = 1.0;
    for (int i = 0; i <= n; i++) {
        if (i != 0) {
            factorial *= (double)i;
            if (isinf(factorial) || isnan(factorial)) {
                free(givenCoeffs);
                free(resultCoeffs);
                return TYPE_OVERFLOW;
            }
        }
        double derivative = 0.0;
        err = GetDerivative(&derivative, i, a, n, givenCoeffs);
        //printf("der: %lf", derivative);
        if (err != OK) {
            free(givenCoeffs);
            free(resultCoeffs);
            return err;
        }
        resultCoeffs[i] = derivative / factorial;
        if (fabs(resultCoeffs[i]) < epsilon) {
            resultCoeffs[i] = 0.0;
        }
    }

    *result = resultCoeffs;
    free(givenCoeffs);
    return OK;
}

void CompareResults(double *coeffs1, double *coeffs2, int n, double x, double a) {
    double result1 = 0.0;
    double result2 = 0.0;
    double x1 = 1.0;
    double x2 = 1.0;
    for (int i = 0; i <= n; i++) {
        if (isinf(x1) || isnan(x1) || isinf(x2) || isnan(x2) || isinf(result1) ||
            isnan(result1) || isinf(result2) || isnan(result2)) {
            LogErrors(TYPE_OVERFLOW);
            printf("Comparison failed.\n");
        }
        result1 += x1 * coeffs1[i];
        result2 += x2 * coeffs2[i];
        x1 *= x;
        x2 *= (x - a);
    }
    printf("%lf\n%lf\n", result1, result2);
}
