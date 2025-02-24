#include "util_task7.h"

int main(int argc, char* argv[]) {
    ParsedArgs args;
    Error err = ParseArgs(argc, argv, &args);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    FILE *inputFile = NULL, *inputFile2 = NULL, *outputFile = NULL;
    err = HandleInputOutput(args, &inputFile, &inputFile2, &outputFile);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    switch (args.wm) {
        case MODE_R:
            HandlerR(inputFile, inputFile2, outputFile);
            break;
        case MODE_A:
            HandlerA(inputFile, outputFile);
            break;
    }

    fclose(inputFile);
    fclose(outputFile);
    if (args.wm == MODE_R) {
        fclose(inputFile2);
    }
    return 0;
}
