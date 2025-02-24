#ifndef UTIL_TASK1_H
#define UTIL_TASK1_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMS,
    INVALID_INPUT,
    INVALID_FLAG,
    OVERFLOW_ERROR,
    MEMORY_ALLOCATION_ERROR
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
int MyStrlen(const char *);
unsigned long long int factorial(int);
void Destroy(void**);

Error StringToInt(const char*, int*);

Error HandleH(int, int**, int*);
Error HandleP(int, bool*);
Error HandleS(int, char**, int*);
Error HandleE(int);
Error HandleA(int, int*);
Error HandleF(int, unsigned long long int*);

void PrintMultiples(const Error, int, int, int*);
void PrintPrimeOrComposite(const Error, int, bool);
void PrintfHex(const Error, const char*, int);
void PrintSum(const Error, int, int);
void PrintFactorial(const Error, int, unsigned long long int);

#endif // UTIL_TASK1_H
