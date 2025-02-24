#ifndef UTIL_TASK_4
#define UTIL_TASK_4
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
  OK,
  WRONG_NUMBER_OF_PARAMETERS,
  MEMORY_ALLOCATION_ERROR,
  INVALID_FLAG,
  INVALID_INPUT,
  OPEN_FILE_FAILURE,
  SAME_FILES_ERROR
} Error;

typedef enum {
  MODE_D,
  MODE_I,
  MODE_S,
  MODE_A,
} WorkMode;

typedef struct {
    WorkMode wm;
    const char *input_file;
    char *output_file;
    int output_file_allocated;
} ParsedArgs;

const char *ErrorToString(Error);
void LogErrors(Error);

void HandlerD(FILE*, FILE*);
void HandlerI(FILE*, FILE*);
void HandlerS(FILE*, FILE*);
void HandlerA(FILE*, FILE*);
char *GenerateOutputFileName(const char *);

Error HandleInputOutput(const char*, char*, FILE**, FILE**);
Error SameFiles(const char*, const char*);
bool MyStrcmp(const char*, const char*);

int ParseArgs(int, char *[], ParsedArgs *);
#endif //UTIL_TASK_4