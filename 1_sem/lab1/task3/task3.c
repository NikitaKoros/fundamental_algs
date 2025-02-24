#include "util_task3.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Error when parsing command line params occured: %s\n",
		        ErrorToString(WRONG_NUMBER_OF_PARAMETERS));
		ShowSpecification();
		return 1;
	}

	Error err;
	WorkMode mode;
    double arguments[4];

	err = CommandArgsHandler(argc, argv, &mode, arguments);

	if (err != OK) {
		fprintf(stderr, "Error when handling parameters occured: %s\n", ErrorToString(err));
		return 1;
	}

	bool answer;
	// Mode Q
	double setOfPermutations[6][3];
	int sizeOfSet;
	double arrOfRoots[6][3];
	// Mode m
	int num1, num2;
	// Mode t
	double sideA, sideB, sideC;

    switch (mode) {
		case MODE_Q:
			err = ModeQHandler(arguments, &setOfPermutations, &arrOfRoots, &sizeOfSet);
			PrintModeQ(err, setOfPermutations, arrOfRoots, sizeOfSet);
			break;
  		case MODE_M:
			err = ModeMHandler(arguments, &num1, &num2, &answer);
			PrintModeM(err, num1, num2, answer);
			break;
  		case MODE_T:
			err = ModeTHandler(arguments, &sideA, &sideB, &sideC, &answer);
			PrintModeT(err, sideA, sideB, sideC, answer);
			break;
	}

    return 0;
}