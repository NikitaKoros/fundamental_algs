#ifndef TASK_10
#define TASK_10


#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 99


typedef enum {
    OK,
    INVALID_INPUT,
    WRONG_BASE,
    BASE_OUT_OF_RANGE,
    ERROR_OVERFLOW
} Error;

Error InputValidation (char*, int, int);
void LogErrors(Error);
const char *ErrorToString(const Error);
void PrintOutput(int, int);
void GetStringInBase(int, int, char [99]);
Error MyStrtol(char [STR_LEN], int, int, int*);


#endif
