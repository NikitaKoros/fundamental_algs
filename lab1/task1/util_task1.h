#ifndef UTIL_TASK1_H
#define UTIL_TASK1_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMS,
    INVALID_INPUT,
    INVALID_FLAG
}Error;

typedef enum {
    FLAG_H,
    FLAG_P,
    FLAG_S,
    FLAG_E,
    FLAG_A,
    FLAG_F
}Flag;

void ShowSpecification();
const char* ErrorToString(const Error);
Error ReadFlag(const char*, Flag*);

Error StringToInt(const char*, long int *);
Error MultipleOfX(int);
Error PrimeOrComposite(int);
Error DevideIntoHex(int);
Error TableOfDegrees(int);
Error SumOfAllNaturals(int);
Error Factorial(int);
int MyPow(int, int);

#endif // UTIL_TASK1_H
