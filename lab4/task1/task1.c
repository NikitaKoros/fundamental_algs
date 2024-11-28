#include "util_task1.h"
#include "hash_table.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        LogErrors(WRONG_NUMBER_OF_PARAMS);
        return 1;
    }
    Error err;
    printf("111\n");
    FILE* file = NULL;
    err = HandleInputOutput(argv[1], &file);
    if (err != OK) {
        LogErrors(err);
        return 1;
    }
    printf("222\n");
    
    HashTable* ht = CreateHashTable(INITIAL_TABLE_SIZE);
    
    err = FillTable(&ht, file);
    if (err != OK) {
        LogErrors(err);
        DestroyTable(ht);
        return 1;
    }
    
    PrintTable(ht);
    
    err = ProcessFile(file, argv[1], ht);
    if (err != OK) {
        LogErrors(err);
        DestroyTable(ht);
        return 1;
    }
    
    printf("\n444\n");
    
    DestroyTable(ht);
    return 0;
}