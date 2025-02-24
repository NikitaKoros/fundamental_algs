#ifndef TAKS_1
#define TASK_1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef enum {
    OK,
    INVALID_FLAG,
    INVALID_INPUT,
    TYPE_OVERFLOW,
    WRONG_NUMBER_OF_PARAMS,
    MEMORY_ALLOCATION_ERROR,
} Error;

typedef enum {
    FLAG_L,
    FLAG_R,
    FLAG_U,
    FLAG_N,
    FLAG_C
} Flag;

typedef Error (*HandlerFunc)(char**, char**, int);

Error HandlerL(char**, char**, int);
Error HandlerR(char**, char**, int);
Error HandlerU(char**, char**, int);
Error HandlerN(char**, char**, int);
Error HandlerC(char**, char**, int);


typedef void (*PrintFunc)(char*);

void PrintOutput(Flag flag, char* output);

void PrintFlagL(char*);
void PrintFlagR(char*);
void PrintFlagU(char*);
void PrintFlagN(char*);
void PrintFlagC(char*);

void LogErrors(Error);
const char *ErrorToString(const Error);

Error ReadFlag(const char*, Flag*);
Error ValidateArgs(int, char**, Flag*);
int MyStrlen(const char *);
Error StringToInt(char*, int*);
Error StringToUnsignedInt(char*, unsigned int*);

#endif