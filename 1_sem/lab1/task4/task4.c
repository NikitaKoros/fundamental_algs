#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util_task4.h"


int main(int argc, char *argv[]) {
    ParsedArgs args;
    Error err = ParseArgs(argc, argv, &args);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    
    FILE* inputFile, *outputFile;
    err = HandleInputOutput(args.input_file, args.output_file, &inputFile, &outputFile);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    
    void (*actions[])(FILE*, FILE*) = {
        HandlerD,
        HandlerI,
        HandlerS,
        HandlerA
    };
    
    if (args.wm >= 0 && args.wm < sizeof(actions)/sizeof(actions[0])) {
        actions[args.wm](inputFile, outputFile);
    }
    
    if (args.output_file_allocated) {
        free(args.output_file);
    }
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}