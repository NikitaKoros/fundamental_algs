#ifndef TASK_9
#define TASK_9

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMETERS,
    INVALID_BASE,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR
} Error;

const char *ErrorToString(Error);
void LogErrors(Error);

Error fillArray(int*, size_t, int, int);
void findAndSwapMinMax(int*, size_t);
Error findNearestValue(int*, size_t, int*, size_t, int*);
int findNearest(int*, size_t, int);
int Comparator(const void*, const void*);

#endif
