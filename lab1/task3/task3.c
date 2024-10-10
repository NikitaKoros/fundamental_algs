#include "util_task3.h"
#include "handlers.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Error when parsing command line params occured: %s\n",
		        ErrorToString(WRONG_NUMBER_OF_PARAMETERS));
		ShowSpecification();
		return 1;
	}

	Error err;
	WorkMode mode;
    double* arguments = malloc(sizeof(double) * 4);

	err = CommandArgsHandler(argc, argv, &mode, arguments);

	if (err != OK) {
		fprintf(stderr, "Error when handling parameters occured: %s\n", ErrorToString(err));
		return 1;
	}

    Error (*HandlerFunctions[]) (const double*) = {
        ModeQHandler,
	    ModeMHandler,
	    ModeTHandler
    };

    err = HandlerFunctions[mode](arguments);

    if (err != OK) {
        fprintf(stderr, "Error when processing arguments of handlers: %s", ErrorToString(err));
        return 1;
    }

    return 0;
}