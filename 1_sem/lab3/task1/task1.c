#include "util_task1.h"

int main() {
    Error err = OK;
    int number = 0;
    unsigned int r = 0;
    char* result = NULL;
    printf("Enter decimal number and power of 2:\n");
    err = ReadInput(&number, &r);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    err = DecimalToBinBase(number, r, &result);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    printf("%s\n", result);
    free(result);
    return 0;
}
