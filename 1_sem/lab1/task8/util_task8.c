#include "util_task8.h"

const char* ErrorToString(const Error error) {
    switch (error) {
        case OPEN_FILE_FAILURE:
            return "OPEN_FILE_FAILURE";
        case SAME_FILES_ERROR:
            return "SAME_FILES_ERROR";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case INVALID_BASE:
            return "INVALID_BASE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occured: %s\n", ErrorToString(err));
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int isAlpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int isAlNum(char ch) {
    return isAlpha(ch) || isDigit(ch);
}

int charToValue(char ch) {
    if (isDigit(ch)) {
        return ch - '0';
    } else if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 10;
    } else if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 10;
    }
    return -1;
}

int findMinBase(const char* num) {
    int maxDigit = 0;
    for (int i = 0; num[i] != '\0'; ++i) {
        if (num[i] == ' ') {
            continue;
        }
        int value = charToValue(num[i]);
        if (value == -1) {
            continue;
        }
        if (value > maxDigit) {
            maxDigit = value;
        }
    }
    if (maxDigit == 0) {
        return 2;
    } else {
        return maxDigit + 1;
    }
}

long long convertToDecimal(const char* num, int base) {
    if (base < 2 || base > 36) {
        LogErrors(INVALID_BASE);
        return -1;
    }

    long long result = 0;
    size_t length = (size_t)strlen(num);

    for (size_t i = 0; i < length; ++i) {
        char c = num[i];
        int value;

        if (isDigit(c)) {
            value = c - '0';
        } else if (isAlpha(c)) {
            value = toupper(c) - 'A' + 10;
        } else if (c == ' ') {
            continue;
        } else {
            LogErrors(INVALID_INPUT);
            return -1;
        }

        if (value >= base) {
            LogErrors(INVALID_INPUT);
            return -1;
        }

        result = result * base + value;
    }
    return result;
}

Error HandleInputOutput(char** argv, FILE** fileInput, FILE** fileOutput) {
    Error err;
    err = SameFiles(argv[1], argv[2]);
    if (err != OK) {
        return err;
    }
    
    *fileInput = fopen(argv[1], "r");
    if (*fileInput == NULL) {
        return OPEN_FILE_FAILURE;
    }

    *fileOutput = fopen(argv[2], "w");
    if (*fileOutput == NULL) {
        fclose(*fileInput);
        return OPEN_FILE_FAILURE;
    }

    return OK;
}

Error SameFiles(char* file1, char* file2) {
    char* path1 = realpath(file1, NULL);
    char* path2 = realpath(file2, NULL);

    if (path1 == NULL || path2 == NULL) {
        free(path1);
        free(path2);
        return OPEN_FILE_FAILURE;
    }

    if (MyStrcmp(file1, file2)) {
        free(path1);
        free(path2);
        return SAME_FILES_ERROR;
    }

    free(path1);
    free(path2);
    return OK;
}

bool MyStrcmp(char* str1, char* str2) {
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

