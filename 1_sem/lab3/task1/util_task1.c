#include "util_task1.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case INVALID_ARGS:
            return "INVALID_ARGS";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error ReadInput(int* number, unsigned int* r) {
    int curR, curNum;
    if (scanf("%d", &curNum) != 1) {
        return INVALID_INPUT;
    }

    if (scanf("%d", &curR) != 1) {
        return INVALID_INPUT;
    }

    if (curR < 1 || curR > 5) {
        return INVALID_ARGS;
    }

    *number = curNum;
    *r = curR;
    return OK;
}

Error DecimalToBinBase(int number, unsigned int r, char** output) {
    unsigned int base = 1 << r;
    char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *result = malloc(sizeof(char) * 65);
    if (result == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    int isNegative = 0;
    if (number < 0) {
        isNegative = 1;
        number = BitwiseNegative(number);
    }
    int index = 0;
    int mask = BitwiseDecrement(base);
    while (number > 0) {
        result[index] = chars[number & mask];
        index = BitwiseIncrement(index);
        number >>= r;
    }

    if (isNegative) {
        result[index] = '-';
        index = BitwiseIncrement(index);
    }

    result[index] = '\0';

    int left = 0;
    int right = BitwiseDecrement(index);
    ReverseString(result, left, right);

    *output = result;
    return OK;
}

int BitwiseIncrement(int number) {
    unsigned int m = 1;
    while (number & m) {
        number = number ^ m;
        m <<= 1;
    }
    number = number ^ m;
    return number;
}

int BitwiseDecrement(int number) {
    unsigned int m = 1;
    while (!(number & m)) {
        number = number ^ m;
        m <<= 1;
    }
    number = number ^ m;
    return number;
}

void ReverseString(char* string, int left, int right) {
    while (left < right) {
        char tmp = string[left];
        string[left] = string[right];
        string[right] = tmp;
        left = BitwiseIncrement(left);
        right = BitwiseDecrement(right);
    }
}

int BitwiseNegative(int number) {
    return BitwiseIncrement(~number);
}