#include "util3.h"

int main(void) {

    char* substring = "n\n\nn";
    char* files[] = {
        "../test2"
    };
    size_t numFiles = sizeof(files) / sizeof(files[0]);
    
    Error err = OK;
    Answer answ = {NULL, 0, 0};
    //find_substring_in_files(substring, &err, 3, "../test1", "../test2", "../test3");
    err = FindSubstringInFiles(&answ, substring, numFiles, files[0]);
    if (err != OK) {
        LogErrors(err);
        DestroyAnswer(&answ);
        return 1;
    }
    for (size_t i = 0; i < answ.size; i++) {
        printf("%s", answ.data[i]);
        free(answ.data[i]);
    }
    free(answ.data);
    return 0;
}