#include "util_task2.h"

void ShowSpecification() {
	printf("Second task:\n");
	printf("./task2.exe <precision>\n");
}

const char* ErrorToString(const Error error) {
	switch (error) {
		case OK:
			return "OK";
		case WRONG_NUMBER_OF_PARAMS:
			return "WRONG_NUMBER_OF_PARAMS";
		case INVALID_INPUT:
			return "INVALID_INPUT";
		case OWERFLOW_ERROR:
			return "OWERFLOW_ERROR";
		case TOO_HIGH_PRECISION:
			return "TOO_HIGH_PRECISION";
		default:
			return "UNKNOWN_ERROR";
	}
}

Error StringToDouble(char* str, double* epsilon) {
	double value = 0.0;
	int sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t') {
		str++;
	}
	///
	while (*str == '-') {
		sign*= -1;
		str++;
	}
	///
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

	double decimalPart = 0.1L;
	while (*str) {
		if ('0' <= *str && *str <= '9') {
			value = value + decimalPart * (*str - '0');
			decimalPart *= 0.1L;
			str++;
		} else {
			return INVALID_INPUT;
		}
	}

	if (sign == -1) {
		return INVALID_INPUT;
	}

	*epsilon = value * sign;
	return OK;
}

double FactorialLog(int n) {
	double result = 0.0;
	for (int i = 1; i <= n; ++i) {
		result += log(i);
	}
	return result;
}

long long CombinationMK(int n, int k) {
	long long result = 1;
	for (int i = 0; i < k; ++i) {
		result *= (n - i);
		result /= (i + 1);
	}
	return result;
}