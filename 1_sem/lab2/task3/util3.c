#include "util3.h"

const char* ErrorToString(const Error error) {
    switch (error) {
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case OPEN_FILE_ERROR:
            return "OPEN_FILE_ERROR";
        case FILE_ERROR:
            return "FILE_ERROR";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occurred: %s\n", ErrorToString(err));
}

Error FindSubstringInFiles(Answer* res, char* substring, size_t n_files, ...) {
    va_list args;
    va_start(args, n_files);
    for (size_t i = 0; i < n_files; i++) {
        char* file_name = va_arg(args, char*);

        FILE* file;
        file = fopen(file_name, "r");
        if (!file) {
            return OPEN_FILE_ERROR;
        }
        size_t substrLen = strlen(substring);
        char* current = substring;
        int line = 1;
        int global_pos = 0;
        int last_global_pos = 0;
        int last_line_pos = 0;
        int old_line_pos = 0;
        int current_line_number = 1;
        char c = 0;
        while (1) {
            // printf("%c", *current);
            // printf("%c", c);
            // printf(" <current - substring: %d>; substrLen: %d\n", (int)(current -
            // substring), (int)substrLen); printf("%c -- %c", *current, c);
            if (*current == '\0' || ((current - substring) == substrLen)) {
                if (last_global_pos < last_line_pos) {
                    last_line_pos = old_line_pos;
                    line = current_line_number;
                }
                // printf("%c", *current);
                // str_pos_t pos = {i, line, last_global_pos - last_line_pos + 1};
                //  vector_push_back(results, pos);
                int len = snprintf(NULL, 0, "File: %d, Line: %d, Position: %d\n", (int)i,
                                   line, (last_global_pos - last_line_pos));
                char* output_str = malloc(len + 1);
                if (output_str == NULL) {
                    fclose(file);
                    va_end(args);
                    return MEMORY_ALLOCATION_ERROR;
                }

                snprintf(output_str, len + 1, "File: %d, Line: %d, Position: %d\n",
                         (int)i, line,
                         (last_global_pos - last_line_pos));  // тут  единичка
                Error err = PushBack(res, output_str);
                if (err != OK) {
                    free(output_str);
                    fclose(file);
                    va_end(args);
                    return err;
                }
                current = substring;
                if (fseek(file, last_global_pos + 1, SEEK_SET) != 0) {
                    fclose(file);
                    va_end(args);
                    return FILE_ERROR;
                }

                global_pos = last_global_pos + 1;
            }
            c = fgetc(file);
            // printf(" %c ", c);

            if (c == EOF) {
                break;
            }
            if (c == '\n') {
                last_line_pos = global_pos + 1;
                line++;
            }
            if (c == *current) {
                if (current == substring) {
                    current_line_number = line;
                    last_global_pos = global_pos;
                    old_line_pos = last_line_pos;
                }
                current++;
            } else {
                if (current != substring) {
                    current = substring;
                    // printf("%c", *current);

                    if (last_global_pos < last_line_pos) {
                        last_line_pos = old_line_pos;
                        line = current_line_number;
                    }
                    if (fseek(file, last_global_pos + 1, SEEK_SET) != 0) {
                        va_end(args);
                        return FILE_ERROR;
                    }
                    global_pos = last_global_pos;
                    last_global_pos++;
                }
                // if (*current == c) {
                //     current++;
                // }
            }
            global_pos++;  // сместить к fgetc?
        }
        fclose(file);
    
    }
    va_end(args);
    return OK;
}

Error PushBack(Answer* ans, char* str) {
    if (ans->size == ans->capacity) {
        ans->capacity = ans->capacity == 0 ? 1 : ans->capacity * 2;
        char** temp = realloc(ans->data, ans->capacity * sizeof(char*));
        if (temp == NULL) {
            return MEMORY_ALLOCATION_ERROR;
        }
        ans->data = temp;
    }

    // char* new_str = malloc(strlen(str) + 1);
    // if (new_str == NULL) {
    //     return MEMORY_ALLOCATION_ERROR;
    // }

    // strcpy(new_str, str);

    ans->data[ans->size] = str;
    ans->size++;
    
    return OK;
}

void DestroyAnswer(Answer* ans) {
    if (ans == NULL) {
        return;
    }
    for (size_t i = 0; i < ans->size; i++) {
        if (ans->data[i] != NULL) {
            free(ans->data[i]); 
        }
    }
    if (ans->data != NULL) {
        free(ans->data);
    }
    ans->size = 0;
    ans->capacity = 0;
}
