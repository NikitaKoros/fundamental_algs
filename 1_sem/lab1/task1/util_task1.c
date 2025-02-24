#include "util_task1.h"

/*

    HANDLERS

*/


Error HandleH(int num, int** numbers, int* sizeNumbers) {
    Error err;
    if (num == 0) {
        return INVALID_INPUT;
    }
    
    if (num < 0) {
        num *= -1;
    }
    
    const int y = 100 / num;
    if (y == 0) {
        numbers = NULL;
        return OK;
    }
    
    *numbers = (int*)malloc(y * sizeof(int));
    if (*numbers == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    
    for (int i = 0; i < y; i++) {
        (*numbers)[i] = num * (i + 1);
    }

    *sizeNumbers = y;
    return OK;
}

Error HandleP(int num, bool* prime) {
    if (num <= 0 || num == 1) {
        return INVALID_INPUT;
    }
    if (num == 2 || num == 3) {
        *prime = true;
        return OK;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        *prime = false;
        return OK;
    }
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            *prime = false;
            return OK;
        }
    }
    *prime = true;
    return OK;
}

Error HandleS(int num, char** hexDigits, int* sizeHex) {
    *hexDigits = (char*)malloc(20 * sizeof(char));
    if (*hexDigits == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    
    if (num == 0) {
        *hexDigits[0] = '0';
        *sizeHex = 1;
        return OK;
    }

    int index = 0;

    if (num < 0) {
        num *= -1;
    }

    while (num > 0) {
        int remainder = num % 16;
        if (remainder < 10) {
            char digit = remainder + '0';
            //printf("%c ", digit);
            (*hexDigits)[index] = remainder + '0';
        } else {
            (*hexDigits)[index] = remainder - 10 + 'A';
        }
        num /= 16;
        //printf("%d \n", num);
        index++;
    }

    *sizeHex = index;
    return OK;
}

Error HandleE(int num) {
    if (num < 1 || num > 10) {
        printf("Error: x must not be greater than 10 or less than 1.\n");
        return INVALID_INPUT;
    }

    printf("Power table for exponents from 1 to %d and bases from 1 to 10:\n", num);
    for (int base = 1; base <= 10; ++base) {
		printf("base %d:\n", base);
		double current = base;
		for (int exp = 1; exp <= num; ++exp) {
			printf("%d^%d = %9.0f\n", base, exp, current);
			current *= (double)base;
		}
		printf("\n");
	}
    return OK;
}

Error HandleA(int num, int* result) {
    int value;

    if (num < 1) {
        return INVALID_INPUT;
    }

    if (num > (INT_MAX / (num + 1))) {
        return OVERFLOW_ERROR;
    }

    value = (num * (num + 1)) / 2;

    *result = value;
    return OK;
}

Error HandleF(int num, unsigned long long int* fact) {
    if (num >= 20) {
        return OVERFLOW_ERROR;
    }
    if (num < 0) {
        return INVALID_INPUT;
    }

    *fact = factorial(num);
    return OK;
}

/*

    PRINT FUNCTIONS

*/

void PrintMultiples(const Error err, int num, int size, int* multiples) {
    if (err != OK) {
        printf("Error: %s.\n", ErrorToString(err));
        printf("There are no multiples of given number.\n");
        return;
    }

    if (multiples == NULL) {
        printf("There are no multiples of given number.\n");
        return;
    }

    printf("Multiples of %d within 100: ", num);
    for (int i = 0; i < size; i++) {
        printf("%d ", multiples[i]);
    }
    printf("\n");
}

void PrintPrimeOrComposite(const Error err, int num, bool prime) {
    if (err != OK) {
        //printf("Error occured: %s. ", ErrorToString(err));
        printf("Number %d is not composite or prime.\n", num);
        return;
    }
    if (prime) {
        printf("Number %d is prime.\n", num);
    } else {
        printf("Number %d is composite.\n", num);
    }
}

void PrintfHex(const Error err, const char* hexDigits, int size) {
    
    if (err != OK) {
        printf("Error occured: %s.\n", ErrorToString(err));
    }
    
    printf("Digits of number in hexadecimal system: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%c", hexDigits[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void PrintSum(const Error err, int num, int sum) {
    if (err == OVERFLOW_ERROR) {
        printf("Error occured: %s.\n", ErrorToString(err));
        return;
    }

    if (err == INVALID_INPUT) {
        printf("Error occured: %s.\n", ErrorToString(err));
        printf("X must be a natural number (greater than or equal to 1).\n");
        return;
    }

    printf("The sum of all natural numbers from 1 to %d is: %d\n", num, sum);
}

void PrintFactorial(const Error err, int number, unsigned long long int fact) {
    if (err == OVERFLOW_ERROR) {
        printf("Error occured: %s.\n", ErrorToString(err));
        printf("Can't calculate factorial from number above 19.");
        return;
    }

    if (err == INVALID_INPUT) {
        printf("Error occured: %s.\n", ErrorToString(err));
        printf("Can calculate factorial only from positive numbers.\n");
        return;
    }

    printf("Factorial of number %d: %lld.\n", number, fact);
}

/*

    UTILITIES

*/

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

Error StringToInt(const char* str, int *res){
    int value = 0;
    int negative = 1;

    if (MyStrlen(str) == 0) {
        return INVALID_INPUT;
    }

    
    int index = 0, len = MyStrlen(str);

    while (index < len) {
        if (str[index] == '-' && value == 0) {
            negative *= -1;
            index++;
            continue;
        } else if ('0' > str[index] || str[index] > '9') {
            return INVALID_INPUT;
        }

        int digit = str[index] - '0';
        if (value > (INT_MAX - digit) / 10) {
            return OVERFLOW_ERROR;
        }
        value = value * 10 + digit;
        index++;
    }

    *res = value * negative;
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
        case OVERFLOW_ERROR:
            return "OVERFLOW_ERROR";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        default:
            return "UNKNOWN_ERROR";

    }
}

Error ReadFlag(const char* str, Flag* flag) {
    Flag curFlag;
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
            curFlag = FLAG_H;
            break;
        case 'p':
            curFlag = FLAG_P;
            break;
        case 's':
            curFlag = FLAG_S;
            break;
        case 'e':
            curFlag = FLAG_E;
            break;
        case 'a':
            curFlag = FLAG_A;
            break;
        case 'f':
            curFlag = FLAG_F;
            break;
        default:
            return INVALID_FLAG;
    }

    str++;
    if ((*str) != '\0' && (*str) != ' ') {
        return INVALID_FLAG;
    }

    *flag = curFlag;
    return OK;
}

int MyStrlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return s - str;
}

unsigned long long int factorial(int num){
    unsigned long long int result = 1;
    while (num > 0) {
		result *= num;
		num--;
	}

    return result;
}

void Destroy(void** something) {
    if (something != NULL) {
        free(*something);
        *something = NULL;
    }
}