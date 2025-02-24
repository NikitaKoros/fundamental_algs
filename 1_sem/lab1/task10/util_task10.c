#include "util_task10.h"

Error InputValidation (char* input, int len, int base) {
    Error err = OK;
    bool hasDigits = false;
    for (int i = 0; i < len; i++) {
        char c = input[i];
        if (c == '-') {
            continue;
        } else if (c <= '9' && c >= '0') {
            if (c - '0' >= base) {
                err = WRONG_BASE;
            }
            hasDigits = true;
        } else if (c >= 'A' && c <= 'Z') {
            if (c - 'A' + 10 >= base) {
                err = WRONG_BASE;
            }
            hasDigits = true;
        } else {
            err = INVALID_INPUT;
            break;
        }
    }
    if(!hasDigits) {
        err = INVALID_INPUT;
    }

    return err;
}

Error MyStrtol(char input[STR_LEN], int len, int base, int* res) {
    len--;
    for (int i = len; i >= 0; i--) {
        char c = input[i];
        if (i == 0 && c == '-') {
            *res = -(*res);
            return OK;
        }
        int mult = 0;
        if ('0' <= c && c <= '9') {
            mult = c - '0';
        } else if ('A' <= c && c <= 'Z') {
            mult = c - 55;
        } 

        if (*res > (INT_MAX - mult) / base) {
            return ERROR_OVERFLOW;
        }

        (*res) += pow(base, len - i) * mult;
    }
    
    return OK;
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch (error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case WRONG_BASE:
            return "WRONG_BASE";
        case BASE_OUT_OF_RANGE:
            return "BASE_OUT_OF_RANGE";
        case ERROR_OVERFLOW:
            return "ERROR_OVERFLOW";
        case OK:
            return "OK";
        default:
            return "UNKNOWN_ERROR";
    }
}

void PrintOutput(int number, int base) {
    int basesArr[5] = {base, 9, 18, 27, 36};
    char output[99];
    printf("Max number:\n");
    for (int i = 0; i < 5; i++) {
        int curBase = basesArr[i];
        GetStringInBase(number, basesArr[i], output);
        printf("Base: %d. Number: %s.\n", curBase, output);
    }
}

void GetStringInBase(int number, int base, char outString[99]) {
    int curLen = 0, outLen = 0;;
    char curString[STR_LEN];
    bool isNegative = false;
    if (number < 0) {
        isNegative = true;
        number = -number;
    }
    while (number > 0) {
        int curDigit = number % base;
        if (curDigit <= 9) {
            curString[curLen] = curDigit + '0';
        } else {
            curString[curLen] = curDigit - 10 + 'A';
        }
        curLen++;
        number /= base;
    }

    if (isNegative) {
        outString[outLen] = '-';
        outLen++;
    }
    for (int i = curLen - 1; i >= 0; i--) {
        outString[outLen++] = curString[i];
    }
    outString[outLen] = '\0';
}
