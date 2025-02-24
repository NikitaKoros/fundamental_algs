#include "util_task7.h"

Error ParseArgs(int argc, char* argv[], ParsedArgs* args) {
    if (argc < 4) {
        return WRONG_NUMBER_OF_PARAMETERS;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/') {
        return INVALID_FLAG;
    }

    if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "/r") == 0) {
        if (argc < 5) {
            return WRONG_NUMBER_OF_PARAMETERS;
        }
        args->wm = MODE_R, args->input_file = argv[2];
        args->input_file2 = argv[3];
        args->output_file = argv[4];
    } else if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "/a") == 0) {
        if (argc < 4) {
            return WRONG_NUMBER_OF_PARAMETERS;
        }
        args->wm = MODE_A, args->input_file = argv[2];
        args->input_file2 = NULL;
        args->output_file = argv[3];
    } else {
        return INVALID_FLAG;
    }
    return OK;
}

const char* ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
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

Error HandlerR(FILE* input1, FILE* input2, FILE* output) {
    char* lex1 = (char*)malloc(sizeof(char) * BUF_SIZE);
    if (!lex1) {
        return MEMORY_ALLOCATION_ERROR;
    }
    char* lex2 = (char*)malloc(sizeof(char) * BUF_SIZE);
    if (!lex2) {
        free(lex1);
        return MEMORY_ALLOCATION_ERROR;
    }
    int first_eof = 0, second_eof = 0;
    
    while (1) {
        if (!first_eof) {
            if (fscanf(input1, "%s", lex1) == EOF) {
                first_eof = 1;
            } else {
                fprintf(output, "%s ", lex1);
            }
        }
        if (!second_eof) {
            if (fscanf(input2, "%s", lex2) == EOF) {
                second_eof = 1;
            } else {
                fprintf(output, "%s ", lex2);
            }
        }
        if (first_eof && second_eof) break;
    }
    free(lex1);
    free(lex2);
    return OK;
}

Error HandlerA(FILE* input, FILE* output) {
    char* lex = (char*)malloc(sizeof(char) * BUF_SIZE);
    if (!lex) {
        return MEMORY_ALLOCATION_ERROR;
    }
    int lex_count = 0;
    
    while (fscanf(input, "%s", lex) != EOF) {
        lex_count++;
        if (lex_count % 10 == 0) {
            for (int i = 0; lex[i]; i++) {
                if (isalpha(lex[i])) lex[i] = (char)tolower(lex[i]);
            }
            for (int i = 0; lex[i]; i++) {
                char base4[8];
                IntToString((int)lex[i], base4, 4);
                fprintf(output, "%s ", base4);
            }
        } else if (lex_count % 2 == 0 && lex_count % 10 != 0) {
            for (int i = 0; lex[i]; i++) {
                if (isalpha(lex[i])) lex[i] = (char)tolower(lex[i]);
            }
            fprintf(output, "%s ", lex);
        } else if (lex_count % 5 == 0 && lex_count % 10 != 0) {
            for (int i = 0; lex[i]; i++) {
                char base8[8];
                IntToString((int)lex[i], base8, 8);
                fprintf(output, "%s ", base8);
            }
        } else {
            fprintf(output, "%s ", lex);
        }
    }
    free(lex);
    return OK;
}

Error HandleInputOutput(ParsedArgs args, FILE** input, FILE** input2, FILE** output) {
    const char* input_file = args.input_file;
    const char* input_file2 = args.input_file2;
    const char* output_file = args.output_file;
    if (args.wm == MODE_A) {
        if (SameFiles(input_file, output_file)) {
            return SAME_FILES_ERROR;
        }
    } else {
        if (SameFiles(input_file, input_file2) || SameFiles(input_file, output_file) ||
            SameFiles(input_file2, output_file)) {
            return SAME_FILES_ERROR;
        }
    }
    
    *output = fopen(output_file, "w");
    if (!*output) {
        return OPEN_FILE_FAILURE;
    }

    *input = fopen(input_file, "r");
    if (!*input) {
        fclose(*output);
        return OPEN_FILE_FAILURE;
    }

    if (input_file2) {
        *input2 = fopen(input_file2, "r");
        if (!*input2) {
            fclose(*output);
            fclose(*input);
            return OPEN_FILE_FAILURE;
        }
    } else {
        *input2 = NULL;
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

#include <stdio.h>
#include <stdlib.h>

char* IntToString(int value, char* str, int base) {
    if (base < 2 || base > 36) {
        return NULL;
    }
    char* end = str;
    int is_negative = 0;
    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;
    }
    do {
        int remainder = value % base;
        *end++ = (remainder < 10) ? (char)(remainder + '0') : (char)(remainder - 10 + 'a');
        value /= base;
    } while (value != 0);
    if (is_negative) {
        *end++ = '-';
    }
    *end = '\0';
    char* start = str;
    --end;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    return str;
}

