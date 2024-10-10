#include "dichotomy_equation.h"
#include "util_task2.h"

int main(const int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr,"Error accured: %s\n", ErrorToString(WRONG_NUMBER_OF_PARAMS));
		ShowSpecification();
		return 1;
	}

	Error err;
	double precision;

	err = StringToDouble(argv[1], &precision);
	if (err != OK) {
		fprintf(stderr, "Error when reading percision from command line: %s\n", ErrorToString(err));
		return 1;
	}

	double low = 0.0;
	double high = 1000.0;

	printf("Calculating the values:\n");
	printf("1. Calculating e:\n");
	printf("\tUsing limit: %lf\n", ELimit(precision));
	printf("\tUsing series: %lf\n", ESeries(precision));
	printf("\tUsing equation: %lf\n\n", CalculateUsingDichotomy(EEquation, high, low, precision));

	printf("2. Calculating pi:\n");
	printf("\tUsing limit: %lf\n", PiLimit(precision));
	printf("\tUsing series: %lf\n", PiSeries(precision));
	printf("\tUsing equation: %lf\n\n", DichotomyForCos(PiEquation, precision));

	printf("3. Calculating ln2:\n");
	printf("\tUsing limit: %lf\n", Ln2Limit(precision));
	printf("\tUsing series: %lf\n", Ln2Series(precision));
	printf("\tUsing equation: %lf\n\n", CalculateUsingDichotomy(Ln2Equation, high, low, precision));

	printf("4. Calculating sqrt2:\n");
	printf("\tUsing limit: %lf\n", Sqrt2Limit(precision));
	printf("\tUsing series: %lf\n", Sqrt2Series(precision));
	printf("\tUsing equation: %lf\n\n", CalculateUsingDichotomy(Sqrt2Equation, high, low, precision));

    printf("5. Calculating gamma:\n");
    printf("\tUsing limit: %lf\n", GammaLimit(precision));
    printf("\tUsing series: %lf\n", GammaSeries(precision));
    printf("\tUsing equation: %lf\n\n", DichotomyForGamma(GammaEquation, high, low, precision));

	return 0;
}