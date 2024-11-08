#include "util_task5.h"
#include "student.h"
#include "api.h"

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

    int count;
    Student* students;
    err = ReadStudents(fileInput, &students, &count);
    if (err != OK) {
        fclose(fileInput);
        fclose(fileOutput);
        LogErrors(err);
        return 1;
    }

    err = InteractiveDialogue(students, count, fileOutput);
    if (err != OK) {
        fclose(fileInput);
        fclose(fileOutput);
        LogErrors(err);
        return 1;
    }

    fclose(fileInput);
    fclose(fileOutput);
    DeleteStudents(students, count);
    return 0;
}