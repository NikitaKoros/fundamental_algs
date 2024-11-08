#include "util_task3.h" 
#include "employee.h"

int main(int argc, char** argv) {

    Error err;

    char* inputPath, *outputPath;
    Flag flag;
    err = ProcessArgs(argc, argv, &inputPath, &outputPath, &flag);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    FILE* fileInput, *fileOutput;
    err = HandleInputOutput(inputPath, outputPath, &fileInput, &fileOutput);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }

    Employee* employees;
    int count;

    err = ReadEmployees(fileInput, &employees, &count);
    if (err != OK) {
        LogErrors(err);
        fclose(fileInput);
        fclose(fileOutput);
        return 1;
    }

    Comparator compArr[2] = {
        ascComparison,
        desComparison
    };

    Comparator comparator = compArr[flag];

    fprintf(fileOutput, "Unsorted employees:\n");
    PrintEmployees(employees, count, fileOutput);

    err = SortEmployees(employees, count, comparator, fileOutput);
    if (err != OK) {
        LogErrors(err);
        free(employees);
        fclose(fileInput);
        fclose(fileOutput);
    }

    fprintf(fileOutput, "Sorted employees:\n");
    PrintEmployees(employees, count, fileOutput);

    DeleteEmployees(employees, count);
    fclose(fileInput);
    fclose(fileOutput);
    return 0;
}