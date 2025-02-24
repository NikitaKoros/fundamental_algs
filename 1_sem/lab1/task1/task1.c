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

    int number = 0;

    err = StringToInt(argv[2], &number);
    if (err != OK) {
        fprintf(stderr, "Error while converting command-line arg into int: %s\n", ErrorToString(err));
        return 1;
    }

    int* numbers = NULL;
    int sizeNumbers;
    bool prime;
    char* hexDigits = NULL;
    int sizeHex;
    unsigned long long int fact;
    int sum;

    switch(flag) {

        case FLAG_H:
            err = HandleH(number,  &numbers, &sizeNumbers);
            PrintMultiples(err, number, sizeNumbers, numbers);
            break;

        case FLAG_P:
            err = HandleP(number, &prime);
            PrintPrimeOrComposite(err, number, prime);
            break;

        case FLAG_S:
            err = HandleS(number, &hexDigits, &sizeHex);
            PrintfHex(err, hexDigits, sizeHex);
            break;

        case FLAG_E:
            err = HandleE(number);
            break;

        case FLAG_A:
            err = HandleA(number, &sum);
            PrintSum(err, number, sum);
            break;

        case FLAG_F:
            err = HandleF(number, &fact);
            PrintFactorial(err, number, fact);
            break;
    }

    
    Destroy((void**)&numbers);
    Destroy((void**)&hexDigits);

    return 0;
}