#include "util_task3.h"

const char *ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "UNKNOWN_ERROR";
    }
}

void ShowSpecification() {
    printf("Task 3:\n");
    printf("./task3.c <flag> <parameters>\n");
    printf("\t-q <real number> <real number> <real number> - quadratic equation from given coefficients.\n");
    printf("\t-m <integer> <integer> - checks if the first number is multiple of the second.\n");
    printf("\t-t <real number> <real number> <real number> <real number> - lengths of the sides of right triangle\n");
}

Error ReadFlag(const char *str, WorkMode *mode) {
    while (*str == ' ' || *str == '\n' || *str == '\t') {
        str++;
    }

    if (*str != '-' && *str != '/') {
        return INVALID_FLAG;
    } else {
        str++;
    }

    switch (*str) {
        case 'q':
            *mode = MODE_Q;
            return OK;
        case 'm':
            *mode = MODE_M;
            return OK;
        case 't':
            *mode = MODE_T;
            return OK;
        default:
            return INVALID_FLAG;
    }
}

double MyAtof(const char* str) {
    double res = 0.0;
    int sign = 1;

    while (*str == ' ' || *str == '\n' || *str == '\t') {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        res = res * 10 + (*str - '0');
        str++;
    }

    if (*str == '.') {
        double decimPart = 1.0;
        str++;
        while (*str >= '0' && *str <= '9') {
            decimPart *= 0.1;
            res += decimPart * (*str - '0');
            str++;
        }
    }

    return sign * res;
}

void PrintRoots(const int numberOfRoots, const double* root1, const double* root2) {
    if (numberOfRoots == 0) {
        printf("The equation doesn't have roots.\n");
    } else if (numberOfRoots == 1) {
        printf("The equation has only one root: %lf.\n", *root1);
    } else {
        printf("Roots of the equation: %lf, %lf.\n", *root1, *root2);
    }
}

int SolveQuadraticEquation(double precision, double a, double b, double c, double* root1, double* root2) {
    double desctiminant = b * b - 4 * a * c;
    if (fabs(desctiminant) < precision) {
        desctiminant = 0.0;
    }

    if (desctiminant < 0) {
        return 0;
    } else if (desctiminant == 0) {
        *root1 = -b / (2.0 * a);
        return 1;
    } else {
        *root1 = (-b - sqrt(desctiminant)) / (2.0 * a);
        *root2 = (-b + sqrt(desctiminant)) / (2.0 * a);
        return 2;
    }
}