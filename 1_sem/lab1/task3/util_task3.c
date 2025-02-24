#include "util_task3.h"

const char *ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case ERROR_ATOF:
            return "ERROR_ATOF";
        case INVALID_FLAG:
            return "INVALID_FLAG";
        case INVALID_PRECISION:
            return "INVALID_PRECISION";
        case INVALID_SIDES_LENGTH:
            return "INVALID_SIDES_LENGTH";
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
    while (isspace(*str)) {
        str++;
    }

    if (*str != '-' && *str != '/') {
        return INVALID_FLAG;
    } else {
        str++;
    }

    WorkMode curMode;
    switch (*str) {
        case 'q':
            curMode = MODE_Q;
            break;
        case 'm':
            curMode = MODE_M;
            break;
        case 't':
            curMode = MODE_T;
            break;
        default:
            return INVALID_FLAG;
    }
    str++;
    if ((*str) != '\0' && !isspace(*str)) {
        

        return INVALID_FLAG;
    }

    *mode = curMode;
    return OK;
}

Error MyAtof(const char* str, double* arg) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int divisor = 1;
    bool hasFraction = false;
    int decimalCount = 0;
    int maxDecimalPlaces = 17;

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

    while (isdigit(*str)) {
        int digit = *str - '0';

        if (sign == 1 && result > (DBL_MAX - digit) / 10) {
            return ERROR_ATOF;
        }
        result = result * 10 + digit;
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

void PrintRoots(const int numberOfRoots, const double* root1, const double* root2) {
    if (numberOfRoots == 0) {
        printf("The equation doesn't have roots.\n");
    } else if (numberOfRoots == 1) {
        printf("The equation has only one root: %lf.\n", *root1);
    } else if (numberOfRoots == 2) {
        printf("Roots of the equation: %lf, %lf.\n", *root1, *root2);
    } else {
        printf("The equation has infinite number of roots.\n");
    }
    printf("\n");
}

int SolveQuadraticEquation(double precision, double a, double b, double c, double* root1, double* root2) {
    
    if (fabs(a) < precision && fabs(b) < precision && fabs(c) < precision) {
        return 3;
    }

    if (fabs(a) < precision) {
        if (fabs(b) > precision) {
            if(fabs(c) < precision) {
                *root1 = 0.0;
                return 1;
            }
            double solution = -c / b;
            *root1 = solution;
            return 1;
        } else if (fabs(c) < precision) {
            return 3;
        } else {
            return 0;
        }
    }

    double discriminant = b * b - 4 * a * c;

    if (fabs(discriminant) < precision) {
        if(fabs(b) < precision) {
                *root1 = 0.0;
                return 1;
        }
        double solution = -b / (2 * a);
        *root1 = solution;

        return 1;

    } else if (discriminant > 0) {
    
        double solution1 = (-b + pow(discriminant, 0.5)) / a * 0.5;
        double solution2 = (-b - pow(discriminant, 0.5)) / a * 0.5;

        *root1 = solution1;
        *root2 = solution2;

        return 2;

    } else {
        return 0;
    }
}

bool CheckMultiples(int firstNumber, int secondNumber){
    if (firstNumber % secondNumber == 0) {
        return true;
    }
    return false;
}

void PrintIfRightTriangle(bool rightTriangle) {
    if (rightTriangle) {
        printf("These are sides of the right triangle.\n");
    } else {
        printf("These are NOT sides of the right triangle.\n");
    }
}

int GetSetOfPermutations(double permutationsArr[6][3], double (*resultSet)[6][3], double precision){
    
    int k = 1;
    for (int j = 0; j < 3; j++) {
        (*resultSet)[0][j] = permutationsArr[0][j];
    }

    for (int i = 1; i < 6; i++) {
        bool isUnique = true;
        for (int j = 0; j < k; j++) {
            if (AreEqualPermutations(permutationsArr[i], (*resultSet)[j], precision)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            for (int j = 0; j < 3; j++) {
                (*resultSet)[k][j] = permutationsArr[i][j];
            }
            k++;
        }
    }
    return k;
}

bool AreEqualPermutations(double perm1[3], double perm2[3], double precision) {
    bool firstCoeff = fabs(perm1[0] - perm2[0]) < precision;
    bool secondCoeff = fabs(perm1[1] - perm2[1]) < precision;
    bool thirdCoeff = fabs(perm1[2] - perm2[2]) < precision;

	return firstCoeff && secondCoeff && thirdCoeff;
}

/*

    PrintHandler's

*/

void PrintModeQ(Error err, double*, double*, int){
    if (err == INVALID_INPUT) {

    }
}

void PrintModeM(Error err, int firstNumber, int secondNumber, bool areMultiples){
    
    if (err == INVALID_INPUT) {
        printf("Numbers should be integers not equal zero.");
        return;
    }

    if (areMultiples) {
        printf("The first number %d is multiple of the second number %d\n", firstNumber, secondNumber);
    } else {
        printf("The first number %d is NOT multiple of the second number %d\n", firstNumber, secondNumber);
    }
    printf("\n");
    
}

void PrintModeT(Error err, double a, double b, double c, bool rightTriangle){
    
    printf("Sides: %lf, %lf, %lf\n", a, b, c);

    if (err ==  INVALID_PRECISION) {
        printf("Precision should be greater than 0.0\n");
        return;
    }

    if (err == INVALID_SIDES_LENGTH) {
        printf("Lengths of triangle's sides should be non-negative.\n");
        return;
    }

    PrintIfRightTriangle(rightTriangle);
}
