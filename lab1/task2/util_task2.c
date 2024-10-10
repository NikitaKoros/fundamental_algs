#include "util_task2.h"

void ShowSpecification() {
	printf("Second task:\n");
	printf("./task2.exe <percision>\n");
}

const char* ErrorToString(const Error error) {
	switch (error) {
		case OK:
			return "OK";
		case WRONG_NUMBER_OF_PARAMS:
			return "WRONG_NUMBER_OF_PARAMS";
		case INVALID_INPUT:
			return "INVALID_INPUT";
		default:
			return "UNKNOWN_ERROR";
	}
}

Error StringToDouble(char* str, double* epsilon) {
	double value = 0.0;

	while (*str == ' ' || *str == '\n' || *str == '\t') {
		str++;
	}

	if (*str == '\0') {
		return INVALID_INPUT;
	}

	while (*str) {
		if ('0' <= *str && *str <= '9') {
			value = value * 10 + (*str - '0');
			str++;
		} else if (*str == '.') {
			str++;
			break;
		} else {
			return INVALID_INPUT;
		}
	}

	if (*str == '\0') {
		return INVALID_INPUT;
	}

	double decimalPart = 0.1;
	while (*str) {
		if ('0' <= *str && *str <= '9') {
			value = value + decimalPart * (*str - '0');
			decimalPart *= 0.1;
			str++;
		} else {
			return INVALID_INPUT;
		}
	}

	*epsilon = value;
	return OK;
}

double Factorial(int k) {
    if (k <= 1) return 1.0;
    long double result = 1.0;
    for (int i = 2; i <= k; i++) {
        result *= i;
    }
    return result;
}

double CombinationKM(int k, int m) {
    return Factorial(m) / (Factorial(k) * Factorial(m - k));
}