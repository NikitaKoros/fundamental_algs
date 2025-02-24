#include "util_task3.h"

Error CommandArgsHandler(const int argc, char **argv, WorkMode *mode, double* args) {
    Error err = ReadFlag(argv[1], mode);
    if (err != OK) {
        return err;
    }

    int argsAmount;
    switch (*mode) {
        case MODE_Q:
            argsAmount = 6;
            break;
        case MODE_M:
            argsAmount = 4;
            break;
        case MODE_T:
            argsAmount = 6;
            break;
        default:
            return INVALID_FLAG;
    }
    if (argsAmount != argc) {
        
        return WRONG_NUMBER_OF_PARAMETERS;
    }

    for (int i = 0; i < argsAmount - 2; i++) {
        double arg;
        err = MyAtof(argv[i + 2], &arg);
        if (err != OK) {
            return err;
        }
        args[i] = arg;
    }

    return OK;
}

Error ModeQHandler(const double* args, double(*serOfPerms)[6][3], double* arrOfRoots, int* setSize) {
    double precision = args[0];
    if (precision <= 0.0) {
        printf("Precision should be greater than 0.0.\n");
        return INVALID_INPUT;
    }

    double a = args[1], b = args[2], c = args[3];

    double argsPermutations[6][3] = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};
    double permutationsSet[6][3];
    int size = GetSetOfPermutations(argsPermutations, &permutationsSet, precision);
    for (int i = 0; i < size; i++) {
        a = permutationsSet[i][0], b = permutationsSet[i][1], c = permutationsSet[i][2];
        printf("Solving quadratic equation with coefficients: a = %.3f, b = %.3f, c = %.3f\n", a, b, c);

        int numberOfRoots;
        double root1, root2;
        
        numberOfRoots = SolveQuadraticEquation(precision, a, b, c, &root1, &root2);
        PrintRoots(numberOfRoots, &root1, &root2);
    }
    return OK;
}

Error ModeMHandler(const double* args, int* num1, int* num2, bool* areMultiple) {
    if (args[0] == 0 || args[1] == 0) {
        return INVALID_INPUT;
    }

    const int firstNumber = (int) args[0];
    const int secondNumber = (int) args[1];

    if (firstNumber != round(args[0]) || secondNumber != round(args[1])) {
        return INVALID_INPUT;
    }

    *num1 = firstNumber;
    *num2 = secondNumber;
    *areMultiple = CheckMultiples(firstNumber, secondNumber);

    return OK;
}

Error ModeTHandler(const double* args, double* sideA, double* sideB, double* sideC, bool* rightTriangle) {
    
    double precision = args[0];
    if (precision <= 0.0) {
        return INVALID_PRECISION;
    }
    double a = args[1];
    double b = args[2];
    double c = args[3];
    if (a < precision || b < precision || c < precision) {
        return INVALID_SIDES_LENGTH;
    }
    double hypotenuse = fmax(fmax(a, b), c);
    double sumOfLegs = a * a + b * b + c * c - hypotenuse * hypotenuse;
    if (fabs(sumOfLegs - hypotenuse * hypotenuse) < precision) {
        *rightTriangle = true;
    } else {
        *rightTriangle = false;
    }

    *sideA = a;
    *sideB = b;
    *sideC = c;

    return OK;
}