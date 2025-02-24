#include "util_task8.h"

int main(int argc, char* argv[]) {
    Error err = OK;

    if (argc != 3) {
        LogErrors(WRONG_NUMBER_OF_PARAMETERS);
        return 1;
    }

    FILE *inputFile, *outputFile;
    err = HandleInputOutput(argv, &inputFile, &outputFile);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    size_t bufferSize = INITIAL_BUFFER_SIZE;
    char* num = (char*)malloc(bufferSize * sizeof(char));

    if (num == NULL) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    size_t index = 0;
    int ch;

    while ((ch = fgetc(inputFile)) != EOF) {
        if (isAlNum((char)ch)) {
            num[index++] = (char)ch;
            if (index >= bufferSize) {
                bufferSize *= 2;
                char* temp = (char*)realloc(num, bufferSize * sizeof(char));
                if (temp == NULL) {
                    LogErrors(MEMORY_ALLOCATION_ERROR);
                    free(num);
                    fclose(inputFile);
                    fclose(outputFile);
                    return 1;
                }
                num = temp;
            }
        } else if (index > 0) {
            num[index] = '\0';
            char* ptr = num;
            while (*ptr == '0') {
                ptr++;
            }
            if (*ptr == '\0') {
                num[0] = '0';
                num[1] = '\0';
            } else {
                memcpy(num, ptr, strlen(ptr) + 1);
            }
            index = strlen(num);

            int minBase = findMinBase(num);
            long long decimalValue = convertToDecimal(num, minBase);

            if (decimalValue != -1) {
                fprintf(outputFile, "%s (base %d) = %lld\n", num, minBase, decimalValue);
            }
            index = 0;
        }
    }

    if (index > 0) {
        num[index] = '\0';
        char* ptr = num;
        while (*ptr == '0') {
            ptr++;
        }
        if (*ptr == '\0') {
            num[0] = '0';
            num[1] = '\0';
        } else {
            memcpy(num, ptr, strlen(ptr) + 1);
        }
        int minBase = findMinBase(num);
        long long decimalValue = convertToDecimal(num, minBase);

        if (decimalValue != -1) {
            fprintf(outputFile, "%s (base %d) = %lld\n", num, minBase, decimalValue);
        }
    }

    free(num);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}