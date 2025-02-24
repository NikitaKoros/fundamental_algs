#ifndef TASK_7
#define TASK_7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUF_SIZE 256

typedef enum {
    OK,
    WRONG_NUMBER_OF_PARAMETERS,
    MEMORY_ALLOCATION_ERROR,
    INVALID_FLAG,
    OPEN_FILE_FAILURE,
    SAME_FILES_ERROR
} Error;

typedef enum { MODE_R, MODE_A } WorkMode;

typedef struct {
    WorkMode wm;
    const char *input_file;
    const char *input_file2;
    const char *output_file;
} ParsedArgs;

Error ParseArgs(int, char **, ParsedArgs *);
Error HandleInputOutput(ParsedArgs, FILE **, FILE **, FILE **);
Error SameFiles(const char*, const char*);
bool MyStrcmp(const char*, const char*);
char* IntToString(int, char*, int);

void LogErrors(Error);
const char *ErrorToString(Error);

Error HandlerR(FILE *, FILE *, FILE *);
Error HandlerA(FILE *, FILE *);

#endif
