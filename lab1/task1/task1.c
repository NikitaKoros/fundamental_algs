#include "util_task1.h"

int main(const int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr,"Error accured: %s\n", ErrorToString(WRONG_NUMBER_OF_PARAMS));
        ShowSpecification();
        return 1;
    }

    Error err;
	Flag flag;

    err = ReadFlag(argv[1], &flag);
    if (err != OK) {
        fprintf(stderr, "Error while reading flag form command-line: %s\n", ErrorToString(err));
        return 1;
    }

    long int number = 0;

    err = StringToInt(argv[2], &number);
    if (err != OK) {
        fprintf(stderr, "Error while converting command-line arg into int: %s\n", ErrorToString(err));
        return 1;
    }

    Error (*funcsArr[]) (int) = {
        MultipleOfX,
        PrimeOrComposite,
        DevideIntoHex,
        TableOfDegrees,
        SumOfAllNaturals,
        Factorial
    };

    err = funcsArr[flag](number);
    if (err != OK) {
        fprintf(stderr, "Error accured: %s\n", ErrorToString(err));
        return 1;
    }

    return 0;
}