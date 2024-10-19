#include "util_task10.h"

int main(int argc, char** argv) {
    char minus;
    int sign = 1;
    while ((minus = fgetc(stdin)) == '-') {
        sign *= -1;
    }
    if (minus != '-') {
        ungetc(minus, stdin);
    }
    int base;
    if (fscanf(stdin, "%d", &base) != 1) {
        printf("Invalid input1.\n");
        return 1;
    }
    char nextChar = fgetc(stdin);
    if (nextChar != '\n' && nextChar != ' ' && nextChar != '\t') {
        printf("Invalid input2.\n");
        return 1;
    }
    base *= sign;
    if (base < 2 || base > 36) {
        printf("Wrong base number.\n");
        return 1;
    }
    char c;
    char current[STR_LEN];
    int curLen = 0;
    int max = INT_MIN;
    Error err = OK;
    bool wereNumbers = false;

    while (true) {
        memset(current, 0, sizeof(current));
        curLen = 0;

        while ((c = getchar()) != '\n' && c != '\t' && c != ' ') {
            if(curLen > STR_LEN) {
                err = INVALID_INPUT;
                break;
            }
            current[curLen] = c;
            curLen++;
        }

        if (curLen == 0) {
            continue;
        }

        if (curLen == 4 && strncmp(current, "Stop", 4) == 0) {
            err = OK;
            break;
        }

        err = InputValidation(current, curLen, base);
        if (err != OK) {
            break;
        }
        wereNumbers = true;
        int decimNumber = 0;
        err = MyStrtol(current, curLen, base, &decimNumber);
        if (err != OK) {
            break;
        }
        if (abs(decimNumber) > abs(max)) {
            max = decimNumber;
        }
    }

    if (err != OK) {
        LogErrors(err);
        return 1;
    }    

    if (!wereNumbers) {
        return 0;
    }
    PrintOutput(max, base);
}