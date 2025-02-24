#include "util_task8.h"

void LogErrors(Error err) {
    fprintf(stdout, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case INVALID_ARG:
            return "INVALID_ARG";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error Summary(BigNumber **result, int base, int count, ...) {
    if (base < 2 || base > 36) {
        return INVALID_ARG;
    }

    Error err = OK;
    va_list args;
    va_start(args, count);

    BigNumber *sum = CreateBigNumber("0", base);
    for (int i = 0; i < count; i++) {
        char *numberStr = va_arg(args, char *);
        //printf("%s\n", numberStr);
        BigNumber *current = CreateBigNumber(numberStr, base);
        if (current == NULL) {
            DestroyBigNumber(sum);
            //printf("2");
            
            return MEMORY_ALLOCATION_ERROR;
        }

        if (sum->len < current->len) {
            SwapBigNumbers(sum, current);
        }

        err = SumBigNumbers(sum, current);
        if (err != OK) {
            DestroyBigNumber(sum);
            DestroyBigNumber(current);
            return err;
        }
        DestroyBigNumber(current);
    }

    va_end(args);
    *result = sum;
    return OK;
}

int CharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

char IntToChar(int value) {
    if (value >= 0 && value <= 9) return (char)('0' + value);
    if (value >= 10 && value <= 35) return (char)('A' + (value - 10));
    return '?';
}

void PrintBigNumber(BigNumber *bigNumber) {
    for (int i = (int) bigNumber->len - 1; i >= 0; i--) {
        printf("%c", IntToChar(bigNumber->buffer[i]));
    }
    printf("\n");
}

void DestroyBigNumber(BigNumber *bigNumber) {
    if (bigNumber->buffer != NULL) {
        free(bigNumber->buffer);
    }
    free(bigNumber);
}

BigNumber *CreateBigNumber(const char *str, int base) {
    //printf("%s", str);
    if (*str == '\0') {
        BigNumber* res = CreateBigNumber("0", base);
        return res;
    }
    BigNumber *result = malloc(sizeof(BigNumber));
    if (!result) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t leadingZeros = 0;
    
    while (leadingZeros < len && str[leadingZeros] == '0') {
        leadingZeros++;
    }
    
    if (leadingZeros == len) {
        leadingZeros = len - 1;
    }
    
    size_t actualLen = len - leadingZeros;
    
    result->len = actualLen;
    result->capacity = actualLen + 1;
    result->buffer = calloc(result->capacity, sizeof(int));
    result->base = base;

    if (!result->buffer) {
        free(result);
        
        return NULL;
    }

    for (size_t i = 0; i < actualLen; i++) {
        int value = CharToInt(str[len - i - 1]);
        
        if (value >= base || value < 0) {
            //printf("%s\n", str);
            
            DestroyBigNumber(result);
            
            //printf("\nvalue: %d, char: %c, str: %s", value, str[len - i - 1], str);
            
            return NULL;
        }
        result->buffer[i] = value;
    }
    return result;
}

Error SumBigNumbers(BigNumber *n1, BigNumber *n2) {
    int carry = 0;
    for (size_t i = 0; i < n2->len; i++) {
        int sum = n1->buffer[i] + n2->buffer[i] + carry;
        n1->buffer[i] = sum % n1->base;
        carry = sum / n1->base;
    }

    for (size_t i = n2->len; i < n1->len; i++) {
        int sum = n1->buffer[i] + carry;
        n1->buffer[i] = sum % n1->base;
        carry = sum / n1->base;
        if (carry == 0) break;
    }

    if (carry > 0) {
        if (n1->len < n1->capacity) {
            n1->buffer[n1->len] = carry;
        } else {
            int *newBuffer = realloc(n1->buffer, n1->capacity * 3 / 2);
            if (!newBuffer) {
                printf("1");
                return MEMORY_ALLOCATION_ERROR;
            }
            n1->buffer = newBuffer;
            n1->capacity = n1->capacity * 3 / 2;
            n1->buffer[n1->len] = carry;
        }
        n1->len++;
    }

    return OK;
}

void SwapBigNumbers(BigNumber *n1, BigNumber *n2) {
    int *tempBuffer = n1->buffer;
    size_t tempLen = n1->len;
    size_t tempCapacity = n1->capacity;
    int tempBase = n1->base;

    n1->buffer = n2->buffer;
    n1->len = n2->len;
    n1->capacity = n2->capacity;
    n1->base = n2->base;

    n2->buffer = tempBuffer;
    n2->len = tempLen;
    n2->capacity = tempCapacity;
    n2->base = tempBase;
}