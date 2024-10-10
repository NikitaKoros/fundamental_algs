#include "util_task4.h"

const char *ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "UNKNOWN_ERROR";
    }
}