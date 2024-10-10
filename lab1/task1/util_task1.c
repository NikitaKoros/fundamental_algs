#include "util_task1.h"

void ShowSpecification() {
    printf("First task:\n");
    printf("\t./task1 <flag> <integer x>\n");
    printf("Possible flags:\n");
    printf("\t-h -- natural numbers multiples of x\n");
    printf("\t-p -- whether x is prime or composite\n");
    printf("\t-s -- devide x into hexadecimal digits\n");
    printf("\t-e -- display the table of degrees\n");
    printf("\t-a -- calculate sum of all natural numbers from 1 to x\n");
    printf("\t-f -- calculate factorial of x\n");
}

Error StringToInt(const char* str, long int *res){
    long int value = 0;
    while (*str == ' ' || *str == '\t' || *str == '\n') {
        str++;
    }

    if (*str == '\0') {
        return INVALID_INPUT;
    }

    while (*str) {
        if ('0' <= *str && *str <= '9') {
            value = value * 10 + (*str - '0');
            str++;
        } else {
            return INVALID_INPUT;
        }
    }
    *res = value;
    return OK;
}

const char* ErrorToString(const Error error) {
    switch (error) {
        case OK:
            return "OK";
        case WRONG_NUMBER_OF_PARAMS:
            return "WRONG_NUMBER_OF_PARAMS";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case INVALID_FLAG:
            return "INVALID_FLAG";
        default:
            return "UNKNOWN_ERROR";

    }
}

Error ReadFlag(const char* str, Flag* flag) {
    while (*str == ' ' || *str == '\n' || *str == '\t') {
        str++;
    }

    if (*str != '-' && *str != '/') {
        return INVALID_FLAG;
    } else {
        str++;
    }

    switch (*str) {
        case 'h':
            *flag = FLAG_H;
            return OK;
        case 'p':
            *flag = FLAG_P;
            return OK;
        case 's':
            *flag = FLAG_S;
            return OK;
        case 'e':
            *flag = FLAG_E;
            return OK;
        case 'a':
            *flag = FLAG_A;
            return OK;
        case 'f':
            *flag = FLAG_F;
            return OK;
        default:
            return INVALID_FLAG;
    }
}

Error MultipleOfX(int num){
    const int y = 100 / num;
    if (y == 0) {
        printf("There are no multiples of given number.\n");
        return OK;
    }

    printf("Multiples of %d within 100: ", num);
    for (int i = 1; i <= y; i++) {
        printf("%d ", num * i);
    }
    printf("\n");
    return OK;
}

Error PrimeOrComposite(int num){
    if (num % 2 == 0 || num % 3 == 0) {
        printf("Number %d is composite.", num);
        return OK;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            printf("Number %d is composite.", num);
            return OK;
        }
    }
    printf("Number %d is prime.", num);
    return OK;
}

Error DevideIntoHex(int num){
    if (num == 0) {
        printf("0\n");
        return OK;
    }

    char hex_digits[20];
    int index = 0;

    while (num > 0) {
        const int remainder = num % 16;
        if (remainder < 10) {
            hex_digits[index++] = remainder + '0';
        } else {
            hex_digits[index++] = remainder - 10 + 'A';
        }
        num /= 16;
    }

    printf("Digits of number in hexadecimal system: ");
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", hex_digits[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");

    return OK;
}

Error TableOfDegrees(int num){
    if (num < 1 || num > 10) {
        printf("Error: x must not be greater than 10 or less than 1.\n");
        return INVALID_INPUT;
    }

    printf("Power table for exponents from 1 to %d and bases from 1 to 10:\n", num);
    printf("==============================================\n");
    printf("| Base |");

    for (int exponent = 1; exponent <= num; exponent++) {
        printf("  ^%d  |", exponent);
    }
    printf("\n==============================================\n");

    for (int base = 1; base <= 10; base++) {
        printf("|  %2d  |", base);
        for (int exponent = 1; exponent <= num; exponent++) {
            printf(" %5d |", MyPow(base, exponent));
        }
        printf("\n==============================================\n");
    }

    return OK;

}

Error SumOfAllNaturals(int num){
    if (num < 1) {
        printf("Error: x must be a natural number (greater than or equal to 1).\n");
        return INVALID_INPUT;
    }

    int sum = (num * (num + 1)) / 2;

    printf("The sum of all natural numbers from 1 to %d is: %d\n", num, sum);
    return OK;
}

Error Factorial(int num){
    int result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }

    printf("Factorial of %d is: %d", num, result);
    return OK;
}

int MyPow(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    }

    int result = 1;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}
