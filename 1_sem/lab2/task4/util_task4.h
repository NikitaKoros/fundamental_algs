#ifndef TASK4
#define TASK4

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef enum {
    OK,
    INVALID_INDEX,
    TYPE_OVERFLOW,
    INVALID_ARGUMENT,
    CONVERTATION_ERROR,
    MEMORY_ALLOCATION_ERROR,
} Error;

const char* ErrorToString(const Error);
void LogErrors(Error);

typedef struct {
    double x;
    double y;
} Vertex;

bool IsConvexPolygon(double, int, ...);
int DirectionOfRotation(Vertex, Vertex, Vertex, double);

Error CalculatePolynom(double*, double, int, ...);

Error FindKaprekarNumbers(bool **, int, int, ...);
Error IsKaprekarNumber(int, int, bool *);
Error GetSubstring(const char *, int, char**);
void IntToString(int, int, char *);
int StringToInt(const char *, int);

#endif