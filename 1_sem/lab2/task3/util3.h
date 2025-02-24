#ifndef TASK3
#define TASK3

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int file;
    int line;
    int column;
} str_pos_t;

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMETERS,
    FILE_ERROR,
    OPEN_FILE_ERROR,
    MEMORY_ALLOCATION_ERROR,
} Error;

typedef struct {
    char** data;
    size_t size;
    size_t capacity;
} Answer;

Error PushBack(Answer*, char*);
void DestroyAnswer(Answer*);

Error FindSubstringInFiles(Answer*, char*, size_t, ...);

const char* ErrorToString(const Error);
void LogErrors(Error);

#endif  // TASK3_H
