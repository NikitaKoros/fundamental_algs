#include "util_task10.h"
#include "tree.h"

int main(int argc, char** argv) {
    
    if (argc != 3) {
        LogErrors(WRONG_NUMBER_OF_PARAMS);
        return 1;
    }

    Error err;
    FILE* fileInput;
    FILE* fileOutput;
    err = HandleInputOutput(argv, &fileInput, &fileOutput);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    char* line = NULL;
    size_t bufSize = 0;
    int lineLength;
    Node* root =  NULL;

    int n = 0;

    while ((lineLength = getline(&line, &bufSize, fileInput)) != -1) {
        if (line[lineLength - 1] == '\n') {
            line[lineLength - 1] = '\0';
        }

        char* line_ptr = line;
        err = MakeTree(&line_ptr, &root);
        if (err != OK) {
            LogErrors(err);
            free(line);
            fclose(fileInput);
            fclose(fileOutput);
            return 1;
        }

        int level = 0;
        PrintTree(root, level, fileOutput);
        fprintf(fileOutput, "\n\n");

        FreeTree(root);
        root = NULL;
    }

    free(line);
    fclose(fileInput);
    fclose(fileOutput);
    return 0;
}