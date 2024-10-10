#ifndef HANDLERS_H
#define HANDLERS_H

#include "util_task3.h"

Error CommandArgsHandler(int, const char**, WorkMode*, double*);

Error ModeQHandler(const double *);
Error ModeMHandler(const double*);
Error ModeTHandler(const double*);

#endif //HANDLERS_H
