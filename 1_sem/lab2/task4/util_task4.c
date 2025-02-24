#include "util_task4.h"

const char *ErrorToString(const Error error) {
    switch (error) {
        case INVALID_INDEX:
            return "INVALID_INDEX";
        case TYPE_OVERFLOW:
            return "TYPE_OVERFLOW";
        case INVALID_ARGUMENT:
            return "INVALID_ARGUMENT";
        case CONVERTATION_ERROR:
            return "CONVERTATION_ERROR";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occurred: %s\n", ErrorToString(err));
}

bool IsConvexPolygon(double eps, int pointsNum, ...) {
    if (pointsNum < 3) {
        return false;
    }
    va_list args;
    va_start(args, pointsNum);

    Vertex a, b, c, firstVertex, secondVertex;

    a.x = va_arg(args, double);
    a.y = va_arg(args, double);
    firstVertex.x = a.x;
    firstVertex.y = a.y;

    b.x = va_arg(args, double);
    b.y = va_arg(args, double);
    secondVertex.x = b.x;
    secondVertex.y = b.y;

    c.x = va_arg(args, double);
    c.y = va_arg(args, double);

    int direction = DirectionOfRotation(a, b, c, eps);
    for (int i = 3; i < pointsNum; i++) {
        a.x = b.x;
        a.y = b.y;

        b.x = c.x;
        b.y = c.y;

        c.x = va_arg(args, double);
        c.y = va_arg(args, double);

        int curDir = DirectionOfRotation(a, b, c, eps);

        if (curDir == 0) {
            continue;
        }
        if (curDir != direction) {
            va_end(args);
            return false;
        }
    }
    va_end(args);
    int penultLastFirstDir = DirectionOfRotation(b, c, firstVertex, eps);
    int lastFirstSecDir = DirectionOfRotation(c, firstVertex, secondVertex, eps);
    return penultLastFirstDir == direction && lastFirstSecDir == direction;
}

int DirectionOfRotation(Vertex a, Vertex b, Vertex c, double eps) {
    double abx = b.x - a.x;
    double aby = b.y - a.y;

    double bcx = c.x - b.x;
    double bcy = c.y - b.y;

    double product = abx * bcy - aby * bcx;
    if (product > eps) {
        return 1;
    } else if (product < -eps) {
        return -1;
    }
    return 0;
}

Error CalculatePolynom(double *result, double x, int coeffsNum, ...) {
    va_list coeffs;
    va_start(coeffs, coeffsNum);
    double curCoeff, curRes = 0, curProduct;

    curCoeff = va_arg(coeffs, double);
    curRes = curCoeff;
    for (int i = 1; i < coeffsNum; i++) {
        curProduct = curRes * x;
        if (curProduct > DBL_MAX || curProduct < -DBL_MAX) {
            va_end(coeffs);
            return TYPE_OVERFLOW;
        }
        curCoeff = va_arg(coeffs, double);
        curRes = curProduct + curCoeff;
    }

    *result = curRes;
    return OK;
}

int StringToInt(const char *str, int base) {
    int num = 0;
    while (*str) {
        char digit = *str;
        str++;
        int value;

        if (digit >= '0' && digit <= '9') {
            value = digit - '0';
        } else if (digit >= 'A' && digit <= 'Z') {
            value = digit - 'A' + 10;
        } else if (digit >= 'a' && digit <= 'z') {
            value = digit - 'a' + 10;
        } else {
            return -1;
        }

        if (value >= base) {
            return -1;
        }

        if (num > INT_MAX / base) {
            return -1;
        }
        num *= base;
        if (num > INT_MAX - value) {
            return -1;
        }

        num += value;
    }
    return num;
}

void IntToString(int num, int base, char *result) {
    char buffer[65];
    int index = 0;

    while (num > 0) {
        int remainder = num % base;
        buffer[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        num /= base;
    }

    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - i - 1];
    }
    result[index] = '\0';
}

Error GetSubstring(const char *str, int index, char **res) {
    if (index < 0 || index > strlen(str)) {
        *res = NULL;
        return INVALID_INDEX;
    }

    char *result = (char *)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        *res = result;
        return MEMORY_ALLOCATION_ERROR;
    }

    strncpy(result, str, index);
    result[index] = '\0';

    *res = result;
    return OK;
}

Error IsKaprekarNumber(int num, int base, bool *kaprekar) {
    Error err = OK;
    if (num == 1) {
        *kaprekar = true;
        return OK;
    }

    int square = num * num;
    char squareStr[65];
    IntToString(square, base, squareStr);
    char *leftSubstr;
    
    int len = strlen(squareStr);
    for (int i = 1; i < len; i++) {
        int leftPart = 0, rigthPart = 0;
        leftSubstr = NULL;
        err = GetSubstring(squareStr, i, &leftSubstr);
        if (err != OK) {
            *kaprekar = false;
            return err;
        }
        leftPart = StringToInt(leftSubstr, base);
        rigthPart = StringToInt(squareStr + i, base);
        if (leftPart == -1 || rigthPart == -1) {
            *kaprekar = false;
            free(leftSubstr);
            return CONVERTATION_ERROR;
        }

        if (rigthPart > 0 && (leftPart + rigthPart == num)) {
            *kaprekar = true;
            free(leftSubstr);
            return OK;
        }
        free(leftSubstr);
    }
    *kaprekar = false;
    return OK;
}

Error FindKaprekarNumbers(bool **kaprekarsArr, int base, int numArgs, ...) {
    Error err = OK;
    va_list args;
    va_start(args, numArgs);

    bool *kaprekars = (bool*)malloc(sizeof(bool) * numArgs);
    if (!kaprekars) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < numArgs; i++) {
        const char *strNum = va_arg(args, const char *);
        int decimalNum = StringToInt(strNum, base);
        if (decimalNum < 0) {
            free(kaprekars);
            return CONVERTATION_ERROR;
        }
        bool curKaprekar = false;
        err = IsKaprekarNumber(decimalNum, base, &curKaprekar);
        if (err != OK) {
            free(kaprekars);
            return err;
        }
        kaprekars[i] = curKaprekar;
    }

    va_end(args);
    *kaprekarsArr = kaprekars;
    return OK;
}
