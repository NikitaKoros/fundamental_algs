#include "util_task10.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case SAME_FILES_ERROR:
            return "SAME_FILES_ERROR";
        case OPEN_FILE_FAILURE:
            return "OPEN_FILE_FAILURE";
        case WRONG_NUMBER_OF_PARAMS:
            return "WRONG_NUMBER_OF_PARAMS";
        default:
            return "UNKNOWN_ERROR";
    }
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

