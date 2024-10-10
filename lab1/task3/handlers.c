#include "handlers.h"


Error CommandArgsHandler(const int argc, const char **argv, WorkMode *mode, double* args) {
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
        args[i] = MyAtof(argv[i + 2]);
    }

    return OK;
}

Error ModeQHandler(const double* args) {
    double precision = args[0];
    if (precision <= 0.0) {
        printf("Precision should be greater than 0.0.\n");
        return INVALID_INPUT;
    }
    double a = args[1], b = args[2], c = args[3];

    double argsPermutations[6][3] = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};
    for (int i = 0; i < 6; i++) {
        a = argsPermutations[i][0], b = argsPermutations[i][1], c = argsPermutations[i][2];
        printf("Solving quadratic equation with coefficients: a = %lf, b = %lf, c = %lf\n", a, b, c);
        double root1, root2;
        int numberOfRoots = SolveQuadraticEcuation(precision, a, b, c, &root1, &root2);

        PrintRoots(numberOfRoots, &root1, &root2);
    }
    return OK;
}

Error ModeMHandler(const double* args) {
    if (args[0] == 0 || args[1] == 0) {
        printf("Numbers must not be equal to zero!\n");
        return INVALID_INPUT;
    }

    const int firstNumber = (int) args[0];
    const int secondNumber = (int) args[1];

    if (firstNumber != round(args[0]) || secondNumber != round(args[1])) {
        return INVALID_INPUT;
    }

    if (firstNumber % secondNumber == 0) {
        printf("The first number %d is multiple of the second number %d\n", firstNumber, secondNumber);
    } else {
        printf("The first number %d is NOT multiple of the second number %d\n", firstNumber, secondNumber);
    }
    return OK;
}

Error ModeTHandler(const double* args) {
    double precision = args[0];
    if (precision <= 0.0) {
        printf("Precision should be greater than 0.0\n");
        return INVALID_INPUT;
    }
    double a = args[1];
    double b = args[2];
    double c = args[3];
    printf("Sides: %lf, %lf, %lf\n", a, b, c);
    if (a < 0 || b < 0 || c < 0) {
        printf("Lengths of triangle's sides should be non-negative.\n");
        return INVALID_INPUT;
    }
    double hypotenuse = fmax(fmax(a, b), c);
    double sumOfLegs = a * a + b * b + c * c - hypotenuse * hypotenuse;
    if (fabs(sumOfLegs - hypotenuse * hypotenuse) < precision) {
        printf("These are sides of the right triangle.\n");
    } else {
        printf("These are not sides of the right triangle.\n");
    }
    return OK;
}