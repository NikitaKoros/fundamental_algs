#include "util_task1.h"
#include "hash_table.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case OPEN_FILE_FAILURE:
            return "OPEN_FILE_FAILURE";
        case WRONG_NUMBER_OF_PARAMS:
            return "WRONG_NUMBER_OF_PARAMS";
        case FILE_PROCESSING_FAILED:
            return "FILE_PROCESSING_FAILED";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error HandleInputOutput(char *fileName, FILE ** file) {
    
    *file = fopen(fileName, "r");
    if (*file == NULL) {
        return OPEN_FILE_FAILURE;
    }
    
    return OK;
}

Error ReadLine(FILE* file, char** line) {
    unsigned int len = 0;
    unsigned int capacity = INITIAL_LINE_LENGTH;
    char* curLine = (char*)malloc(sizeof(char) * capacity);
    if (!curLine) {
        return MEMORY_ALLOCATION_ERROR;
    }
    
    char c;
    while ((c = (char)fgetc(file)) != EOF && c != '\n') {
        curLine[len++] = c;
        if (len >= capacity) {
            capacity *= 2;
            char *newLine = (char*)realloc(curLine, capacity * sizeof(char));
            if (!newLine) {
                free(curLine);
                return MEMORY_ALLOCATION_ERROR;
            }
            curLine = newLine;
        }
    }
    
    if (len == 0 && c == EOF) {
        free(curLine);
        return END_OF_FILE;
    }
    
    curLine[len] = '\0';
    *line = curLine;
    return OK;
}

char *strndup(const char *src, size_t n) {
    size_t len = strnlen(src, n);
    char *dst = (char *)malloc(len + 1);
    if (!dst) {
        return NULL;
    }
    memcpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

size_t strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

char *strdup(const char *src) {
    size_t len = strlen(src);
    char *dst = (char *)malloc(len + 1);
    if (!dst) {
        return NULL;
    }
    memcpy(dst, src, len + 1);
    return dst;
}

int NextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int GetNewTableSize(int currentSize) {
    return NextPrime(currentSize * 2);
}