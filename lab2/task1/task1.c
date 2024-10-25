#include "util_task1.h"


int main(int argc, char** argv) {
    Error err;
    Flag flag;
    err = ValidateArgs(argc, argv, &flag);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    HandlerFunc handlesArray[5] = {
        HandlerL,
        HandlerR,
        HandlerU,
        HandlerN,
        HandlerC,
    };

    char** strings = malloc(sizeof(char*) * (argc - 2));
    if (strings == NULL) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        return 1;
    }
    
    for (int i = 0; i < argc - 2; i++) {
        strings[i] = argv[i + 2];
    }

    char* output = NULL;
    err = handlesArray[flag](strings, &output, argc - 2);

    if (err != OK) {
        LogErrors(err);
        free(strings);
        return 1;
    }

    PrintOutput(flag, output);

    free(strings);
    free(output);

}