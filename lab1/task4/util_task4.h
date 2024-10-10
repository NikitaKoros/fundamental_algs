#ifndef UTIL_TASK_4
#define UTIL_TASK_4

typedef enum {
  OK,
  WRONG_NUMBER_OF_PARAMETERS,
  INVALID_INPUT
} Error;

typedef enum {
  MODE_D,
  MODE_I,
  MODE_S,
  MODE_A
} WorkMode;

const char *ErrorToString(Error);
void ShowSpecification();
Error ReadFlag(const char *, WorkMode *);

#endif //UTIL_TASK_4