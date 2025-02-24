#include "util_task6.h"
#include "integrals.h"

int main(int argc, char** argv) {
    if (argc != 2) {
		fprintf(stderr, "Error when parsing command line params occured: %s\n",
		        ErrorToString(WRONG_NUMBER_OF_PARAMETERS));
		ShowSpecification();
		return 1;
	}

    Error err;
    double precision;

    err = ReadPrecision(argv[1], &precision);
    if (err != OK) {
        fprintf(stderr, "Error when reading precision occured: %s\n", ErrorToString(err));
        return 1;
    }
    
    if (precision <= 0.0) {
        printf("Precision can't be equal or less than 0.0\n");
        return 0;
    }

    if (precision <= 0.00000001) {
        printf("Precision is too high.\n");
        return 0;
    }
    printf("Precision: %lf\n", precision);
    double result;
    double integrateFrom = 0.00001;
    double integrateTo = 1.0;
    FuncOfIntegral integralsArray[] = {IntegralA, IntegralB, IntegralC, IntegralD};

    for (int i = 0; i < 4; i++) {
        err = Integrate(precision, integralsArray[i], &result);
        if (err != OK) {
            LogErrors(err);
            continue;
        }
        printf("Integral %c = %lf\n", 'A' + i, result);
    }

    return 0;
}