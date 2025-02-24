#include "util_task3.h"

void LogErrors(Error err) {
    fprintf(stderr, "Error occured: %s\n", ErrorToString(err));
}

const char *ErrorToString(const Error error) {
    switch(error) {
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case WRONG_NUMBER_OF_PARAMS:
            return "WRONG_NUMBER_OF_PARAMS";
        case INVALID_FLAG:
            return "INVALID_FLAG";
        case OPEN_FILE_ERROR:
            return "OPEN_FILE_ERROR";
        case SAME_FILES_ERROR:
            return "SAME_FILES_ERROR";
        case FILE_READ_ERROR:
            return "FILE_READ_ERROR";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERRO";
        case EMPLY_INVALID_ID:
            return "EMPLY_INVALID_ID";
        case EMPLY_INVALID_NAME:
            return "EMPLY_INVALID_NAME";
        case EMPLY_INVALID_SALARY:
            return "EMPLY_INVALID_SALARY";
        default:
            return "UNKNOWN_ERROR";
    }
}

Error ProcessArgs(int argc, char** argv, char** inputPath, char** outputPath, Flag* flag) {
    if (argc != 4) {
        return WRONG_NUMBER_OF_PARAMS;
    }

    *inputPath = argv[1];
    *outputPath = argv[3];

    Error err;
    err = ReadFlag(argv[2], flag);
    if (err != OK) {
        return err;
    }

    return OK;
}

Error HandleInputOutput(char* inputPath, char* outputPath, FILE** fileInput, FILE** fileOutput) {
    Error err;
    err = SameFiles(inputPath, outputPath);
    if (err != OK) {
        return err;
    }
    
    *fileInput = fopen(inputPath, "r");
    if (*fileInput == NULL) {
        return OPEN_FILE_ERROR;
    }

    *fileOutput = fopen(outputPath, "w");
    if (*fileOutput == NULL) {
        fclose(*fileInput);
        return OPEN_FILE_ERROR;
    }

    return OK;
}

Error SameFiles(char* file1, char* file2) {
    char* path1 = realpath(file1, NULL);
    char* path2 = realpath(file2, NULL);

    if (path1 == NULL || path2 == NULL) {
        free(path1);
        free(path2);
        return OPEN_FILE_ERROR;
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

Error ReadFlag(const char* str, Flag* flag) {
    Flag curFlag;
    while (*str == ' ' || *str == '\n' || *str == '\t') {
        str++;
    }

    if (*str != '-' && *str != '/') {
        return INVALID_FLAG;
    }
    
    str++;

    switch (*str) {
        case 'a':
            curFlag = FLAG_A;
            break;
        case 'd':
            curFlag = FLAG_D;
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

Error ReadName(FILE* fileInput, char** name) {
    int len = 0;
    int capacity = 10;
    char* curName = (char*)malloc(sizeof(char) * capacity);
    if (!curName) {
        return MEMORY_ALLOCATION_ERROR;
    }

    char c;
    while (isalpha(c = fgetc(fileInput))) {
        curName[len++] = c;
        if (len >= capacity) {
            capacity *= 2;
            char* newName = (char*)realloc(*name, capacity * sizeof(char));
            if (!newName) {
                free(curName);
                return MEMORY_ALLOCATION_ERROR;
            }
            curName = newName;
        }
    }

    ungetc(c, fileInput);

    if (len == 0) {
        free(curName);
        return EMPLY_INVALID_NAME;
    }

    curName[len] = '\0';
    *name = curName;
    return OK;
}