#include "util_task6.h"



const char *ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case ERROR_ATOF:
            return "ERROR_ATOF";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error ReadPrecision(char* inputString, double* resPrecision) {
    double precision;
    Error err;
    err = MyAtof(inputString, &precision);
    if (err != OK) {
        return err;
    }
    
    *resPrecision = precision;
    return OK;
}


void ShowSpecification (){
    printf("Task 6:\n");
    printf("Usage: ./task6 <double>\n");
    printf("Calculates following integrals with given precision:\n");
    printf("Integral a: ln(x + 1) / x\n");
	printf("Integral b: e^-(x^2 / 2)\n");
	printf("Integral c: ln 1/(1-x)\n");
	printf("Integral d: x^x\n");
}

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

Error MyAtof(const char* str, double* arg) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int divisor = 1;
    bool hasFraction = false;
    int decimalCount = 0;
    int maxDecimalPlaces = 17;
    int maxIntPlaces = 15;
    int intCount = 0;

    while (isspace(*str)) {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    if (!isdigit(*str) && *str != '.') {
        return ERROR_ATOF;
    }

    if (intCount > maxIntPlaces) {
        return ERROR_ATOF;
    }

    while (isdigit(*str)) {
        int digit = *str - '0';

        if (sign == 1 && result > (DBL_MAX - digit) / 10) {
            return ERROR_ATOF;
        }
        result = result * 10 + digit;
        intCount++;
        str++;
    }

    if (*str == '.') {
        hasFraction = true;
        str++;
        while (isdigit(*str) && decimalCount < maxDecimalPlaces) {
            int digit = *str - '0';

            if (sign == 1 && result > (DBL_MAX - digit) / 10) {
                return ERROR_ATOF;
            }

            fraction = fraction * 10 + digit;
            divisor *= 10;
            decimalCount++;
            str++;
        }
    }

    if (hasFraction) {
        result += fraction / divisor;
    }

    if (*str != '\0' && !isspace(*str) && decimalCount < maxDecimalPlaces) {
        return ERROR_ATOF;
    }

    while(isdigit(*str)){
        str++;
    }

    if (*str != '\0') {
        return ERROR_ATOF;
    }

    *arg = sign * result;
    return OK;
}