#ifndef TASK_8
#define TASK_8

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum {
    OK,
    MEMORY_ALLOCATION_ERROR,
    INVALID_ARG
} Error;



typedef struct {
    int base;
    size_t len;
    size_t capacity;
    int *buffer;
} BigNumber;

void PrintBigNumber(BigNumber *);
BigNumber *CreateBigNumber(const char *, int);
void DestroyBigNumber(BigNumber *);
Error SumBigNumbers(BigNumber *, BigNumber *);
void SwapBigNumbers(BigNumber *, BigNumber *);

int CharToValue(char);
char IntToChar(int);

Error Summary(BigNumber **, int, int, ...);

void LogErrors(Error);
const char *ErrorToString(const Error);

#endif