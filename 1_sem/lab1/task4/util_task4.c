#include "util_task4.h"

const char* ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        case INVALID_FLAG:
            return "INVALID_FLAG";
        case OPEN_FILE_FAILURE:
            return "OPEN_FILE_FAILURE";
        case SAME_FILES_ERROR:
            return "SAME_FILES_ERROR";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occured: %s\n", ErrorToString(err));
}

void HandlerD(FILE* inputFile, FILE* outputFile) {
    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (!isdigit(c)) {
            fputc(c, outputFile);
        }
    }
}

void HandlerI(FILE* inputFile, FILE* outputFile) {
    char line[1024];
    while (fgets(line, sizeof(line), inputFile)) {
        int count = 0;
        for (size_t i = 0; line[i] != '\0'; i++) {
            if (isalpha(line[i]) && isascii(line[i])) {
                count++;
            }
        }
        fprintf(outputFile, "%d\n", count);
    }
}

void HandlerS(FILE* inputFile, FILE* outputFile) {
    char line[1024];
    while (fgets(line, sizeof(line), inputFile)) {
        int count = 0;
        for (size_t i = 0; line[i] != '\0'; i++) {
            if (!isalpha(line[i]) && !isdigit(line[i]) && line[i] != ' ') {
                count++;
            }
        }
        fprintf(outputFile, "%d\n", count);
    }
}

void HandlerA(FILE* inputFile, FILE* outputFile) {
    int c;
        while ((c = fgetc(inputFile)) != EOF) {
            if (isdigit(c)) {
                fputc(c, outputFile);
            } else {
            char hex[5];
            snprintf(hex, sizeof(hex), "%X", c);
            fputs(hex, outputFile);
        }
    }
}

char* GenerateOutputFileName(const char* inputFile) {
    const char* lastSlash = strrchr(inputFile, '/');
    const char* fileName;
    if (lastSlash == NULL) {
        fileName = inputFile;
    } else {
        fileName = lastSlash + 1;
    }
    
    // const char* directory;
    // if (lastSlash == NULL) {
    //     directory = ".";
    // } else {
    //     directory = inputFile;
    // }
    
    size_t directoryLen;
    if (lastSlash == NULL) {
        directoryLen = 0;
    } else {
        directoryLen = lastSlash - inputFile;
    }
    
    size_t fileNameLen = strlen(inputFile);
    size_t outputLen = directoryLen + 4 + fileNameLen + 1;
    char* outputFile = malloc(outputLen);
    if (!outputFile) {
        return NULL;
    }
    
    if (directoryLen > 0) {
        strncpy(outputFile, inputFile, directoryLen);
        outputFile[directoryLen] = '\0';
        strcat(outputFile, "/out_");
    } else {
        strcpy(outputFile, "out_");
    }
    strcat(outputFile, fileName);
    return outputFile;
}

Error HandleInputOutput(const char* inPath, char* outPath, FILE** fileInput, FILE** fileOutput) {
    Error err;
    err = SameFiles(inPath, outPath);
    if (err != OK) {
        
        return err;
    }

    *fileInput = fopen(inPath, "r");
    if (*fileInput == NULL) {
        return OPEN_FILE_FAILURE;
    }

    *fileOutput = fopen(outPath, "w");
    if (*fileOutput == NULL) {
        fclose(*fileInput);
        
        return OPEN_FILE_FAILURE;
    }

    return OK;
}

Error SameFiles(const char* file1, const char* file2) {
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

bool MyStrcmp(const char* str1, const char* str2) {
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

int ParseArgs(int argc, char *argv[], ParsedArgs *args) {
    if (argc < 3) {
        return WRONG_NUMBER_OF_PARAMETERS;
    }

    char *flag = argv[1];
    if (flag[0] != '-' && flag[0] != '/') {
        return INVALID_FLAG;
    }

    if (strlen(flag) < 2) {
        return INVALID_FLAG;
    }

    char second_char = flag[1];
    int has_n = (second_char == 'n');

    char action_char = flag[strlen(flag) - 1];
    WorkMode wm;

    switch (action_char) {
        case 'd':
            wm = MODE_D;
            break;
        case 'i':
            wm = MODE_I;
            break;
        case 's':
            wm = MODE_S;
            break;
        case 'a':
            wm = MODE_A;
            break;
        default:
            return INVALID_FLAG;
    }
    
    const char *input_file = argv[2];
    char *output_file = NULL;
    int output_file_allocated = 0;
    
    if (has_n) {
        if (argc != 4) {
            return WRONG_NUMBER_OF_PARAMETERS;
        }
        output_file = argv[3];
        output_file_allocated = 0;
    } else {
        output_file = GenerateOutputFileName(input_file);
        if (!output_file) {
            return MEMORY_ALLOCATION_ERROR;
        }
        output_file_allocated = 1;
    }
    
    args->wm = wm;
    args->input_file = input_file;
    args->output_file = output_file;
    args->output_file_allocated = output_file_allocated;
    
    return OK;
}