#include "util_task1.h"


void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_FLAG:
            return "INVALID_FLAG";
        case WRONG_NUMBER_OF_PARAMS:
            return "WRONG_NUMBER_OF_PARAMS";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        default:
            return "UNKNOWN_ERROR";

    }
}

void PrintOutput(Flag flag, char* output) {
    PrintFunc printsArray[5] = {
        PrintFlagL,
        PrintFlagR,
        PrintFlagU,
        PrintFlagN,
        PrintFlagC
    };

    printsArray[flag](output);
}

void PrintFlagL(char *output) {
    printf("The length of given string is: %s\n", output);
}

void PrintFlagR(char * output) {
    printf("Reversed string:\n%s\n", output);
}

void PrintFlagU(char * output) {
    printf("String with some upper characters:\n%s\n", output);

}

void PrintFlagN(char * output) {
    printf("String with separated characters:\n%s\n", output);

}

void PrintFlagC(char * output) {
    printf("Concatenated string:\n%s\n", output);
}


Error ReadFlag(const char* str, Flag* flag) {
    Flag curFlag;
    while (*str == ' ' || *str == '\n' || *str == '\t') {
        str++;
    }

    if (*str != '-') {
        return INVALID_FLAG;
    }
    
    str++;

    switch (*str) {
        case 'l':
            curFlag = FLAG_L;
            break;
        case 'r':
            curFlag = FLAG_R;
            break;
        case 'u':
            curFlag = FLAG_U;
            break;
        case 'n':
            curFlag = FLAG_N;
            break;
        case 'c':
            curFlag = FLAG_C;
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

Error ValidateArgs(int argc, char** argv, Flag* flag) {
    int numberOfParams;
    if (argc < 2) {
        return WRONG_NUMBER_OF_PARAMS;
    }
    Error err = ReadFlag(argv[1], flag);
    if (err != OK) {
        return err;
    }
    switch (*flag) {
        case FLAG_C:
            if (argc < 4) return WRONG_NUMBER_OF_PARAMS;
            break;
        default:
            if (argc != 3) return WRONG_NUMBER_OF_PARAMS;
            break;
    }
    
    return OK;
}

int MyStrlen(const char *str) {
    const char *s = str;
    while (*s != '\0') {
        s++;
    }
    return s - str;
}

Error StringToUnsignedInt(char* input, unsigned int* number) {
    if (input == NULL || *input == '\0') {
        return INVALID_INPUT;
    }

    int sign = 1;
    unsigned int value = 0;
    int digit;
    char* ptr = input;

    while((*ptr) == '-' || (*ptr) == '+') {
        if ((*ptr) == '-') sign *= -1;
        ptr++;
    }

    if (sign == -1) {
        return INVALID_INPUT;
    }

    while (*ptr != '\0') {
        if (*ptr < '0' || *ptr > '9') {
            return INVALID_INPUT;
        }

        digit = (*ptr) - '0';
        if (value > (UINT_MAX - digit) / 10) {
            return TYPE_OVERFLOW;
        }

        value = value * 10 + digit;
        ptr++;
    }

    *number = value;
    return OK;
}

// Error StringToInt(char* input, int* number) {
//     if (input == NULL || *input == '\0') {
//         return INVALID_INPUT;
//     }

//     int sign = 1;
//     int value = 0;
//     int digit;
//     char* ptr = input;

//     while((*ptr) == '-' || (*ptr) == '+') {
//         if ((*ptr) == '-') sign *= -1;
//         ptr++;
//     }

//     while (*ptr != '\0') {
//         if (*ptr < '0' || *ptr > '9') {
//             return INVALID_INPUT;
//         }

//         digit = (*ptr) - '0';
//         if (value > (INT_MAX - digit) / 10) {
//             return TYPE_OVERFLOW;
//         }

//         value = value * 10 + digit;
//         ptr++;
//     }

//     *number = value * sign;
//     return OK;
// }

Error IntToString(int number, char** output) {
    int numberLength = ceil(log10(number));
    char* curString = malloc(sizeof(char) * (numberLength + 1));
    if (curString == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    curString[numberLength] = '\0';
    for (int i = 1; i <= numberLength; i++) {
        char digit = number % 10 + '0';
        curString[numberLength - i] = digit;
        number /= 10;
    }

    *output = curString;
    return OK;
}

char ToUpper(char c) {
    if (c < 'a' || c > 'z') {
        return c;
    }
    return c - ('a' - 'A');
}

void SortBetweenArrs(char* input, char* numbers, char* letters, char* otherSymbols, char* output, int length) {
    int i = 0, n = 0, l = 0, o = 0;
    for (i; i < length; i++) {
        
        char digit = input[i];
        if (digit == '\0') {
            break;
        }

        if (digit >= '0' && digit <= '9') {
            numbers[n++] = input[i];
        } else if ((digit >= 'a' && digit <= 'z') || (digit >= 'A' && digit <= 'Z')) {
            letters[l++] = input[i];
        } else {
            otherSymbols[o++] = input[i];
        }
    }
    numbers[n] = '\0';
    letters[l] = '\0';
    otherSymbols[o] = '\0';

    i = 0;
    char* arrayOfArrays[] = {numbers, letters, otherSymbols};

    for (int j = 0; j < 3; j++) {
        for (int k = 0; arrayOfArrays[j][k] != '\0'; k++) {
            output[i++] = arrayOfArrays[j][k];
        }
    }
    output[i] = '\0';
}

void ShuffleStrings(char** stringsArray, int length) {
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* tempString = stringsArray[i];
        stringsArray[i] = stringsArray[j];
        stringsArray[j] = tempString;
    }
}

Error HandlerL(char** input, char** output, int paramsCount){
    Error err;
    int length = MyStrlen(*input);
    char* string;
    err = IntToString(length, &string);
    *output = string;
    return OK;
}

Error HandlerR(char** input, char**output, int paramsCount){
    char* string = input[0];
    int length = MyStrlen(string);

    char* resString = malloc(sizeof(char) * (length + 1));
    if (!resString) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < length; i++) {
        resString[i] = string[length - 1 - i];
    }
    resString[length] = '\0';

    *output = resString;
    return OK;
}

Error HandlerU(char** input, char**output, int paramsCount){
    char* string = input[0];
    int length = MyStrlen(string);

    char* resString = malloc(sizeof(char) * (length + 1));
    if (!resString) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < length; i++) {
        resString[i] = (i % 2) ? ToUpper(string[i]) : string[i];
    }

    resString[length] = '\0';
    *output = resString;
    return OK;
}

Error HandlerN(char** input, char**output, int paramsCount){
    
    char* string = input[0];
    int length = MyStrlen(string);

    char* numbers = malloc(sizeof(char) * (length + 1));
    if (!numbers) return MEMORY_ALLOCATION_ERROR;

    char* letters = malloc(sizeof(char) * (length + 1));
    if (!letters) {
        free(numbers);
        return MEMORY_ALLOCATION_ERROR;
    }

    char* otherSymbols = malloc(sizeof(char) * (length + 1));
    if (!otherSymbols) {
        free(numbers);
        free(letters);
        return MEMORY_ALLOCATION_ERROR;
    } 

    *output = malloc(sizeof(char) * (length + 1));
    if (!*output) {
        free(numbers);
        free(letters);
        free(otherSymbols);
        return MEMORY_ALLOCATION_ERROR;
    }

    SortBetweenArrs(string, numbers, letters, otherSymbols, *output, length);

    free(numbers);
    free(letters);
    free(otherSymbols);

    return OK;
}

Error HandlerC(char** input, char** output, int paramsCount) {
    Error err;
    unsigned int seed;
    err = StringToUnsignedInt(input[0], &seed);
    if (err != OK) {
        return err;
    }
    srand(seed);

    int stringsArrLength = paramsCount - 1;
    // int stringsArrLength = 0;
    // int i = 0;
    // while (input[i] != NULL) {
    //     stringsArrLength++;
    //     i++;
    // }
    
    char **stringsArr = malloc(sizeof(char*) * stringsArrLength);
    if (!stringsArr) return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < stringsArrLength; i++) {
        stringsArr[i] = input[i + 1];
    }

    ShuffleStrings(stringsArr, stringsArrLength);

    int totalLength = 0;
    for (int i = 0; i < stringsArrLength; i++) {
        totalLength += MyStrlen(stringsArr[i]);
    }

    char *curOut = malloc(sizeof(char) * (totalLength + 1));
    if (!curOut) {
        free(stringsArr);
        return MEMORY_ALLOCATION_ERROR;
    }

    int index = 0;
    for (int i = 0; i < stringsArrLength; i++) {
        for (char * j = stringsArr[i]; *j; j++) {
            curOut[index++] = *j;
        }
    }
    curOut[index] = '\0';
    *output = curOut;
    free(stringsArr);
    return OK;
}
