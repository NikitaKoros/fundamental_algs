#include "util_task9.h"
#define MAX_SIZE 1000

int main(int argc, char* argv[]) {
    Error err = OK;
    
    if (argc != 4) {
        LogErrors(WRONG_NUMBER_OF_PARAMETERS);
        printf("Usage: %s <size> <min> <max>\n", argv[0]);
        return 1;
    }

    srand((unsigned int)time(NULL));

    // 1
    size_t sizeA1 = (size_t)atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    int* arrayA1 = (int*)malloc((long unsigned int)sizeA1 * sizeof(int));
    if (arrayA1 == NULL) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        return 1;
    }
    
    err = fillArray(arrayA1, sizeA1, min, max);
    if (err != OK) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        free(arrayA1);
        return 1;
    }
    printf("First Array A (before swapping min and max):\n");
    for (size_t i = 0; i < sizeA1; i++) {
        printf("%d ", arrayA1[i]);
    }
    printf("\n\n");

    findAndSwapMinMax(arrayA1, sizeA1);

    printf("First Array A (after swapping min and max):\n");
    for (size_t i = 0; i < sizeA1; i++) {
        printf("%d ", arrayA1[i]);
    }
    printf("\n\n");

    free(arrayA1);

    //2
    size_t sizeA2 = 10;
    size_t sizeB = 10;
    
    // int Min = 10;
    // int Max = 10000;
    // size_t sizeA2 = (size_t)(Min + rand() % (Max - Min + 1));
    // size_t sizeB = (size_t)(Min + rand() % (Max - Min + 1));

    int* arrayA2 = (int*)malloc((long unsigned int)sizeA2 * sizeof(int));
    if (arrayA2 == NULL) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        return 1;
    }

    int* arrayB = (int*)malloc((long unsigned int)sizeB * sizeof(int));
    if (arrayB == NULL) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        free(arrayA2);
        return 1;
    }

    err = fillArray(arrayA2, sizeA2, 10, 10000);
    if (err != OK) {
        LogErrors(err);
        free(arrayA2);
        free(arrayB);
        return 1;
    }
    
    err = fillArray(arrayB, sizeB, -1000, 1000);
    if (err != OK) {
        LogErrors(err);
        free(arrayA2);
        free(arrayB);
        return 1;
    }

    printf("Second Array A:\n");
    for (size_t i = 0; i < sizeA2; i++) {
        printf("%d ", arrayA2[i]);
    }
    printf("\n");

    printf("Array B:\n");
    for (size_t i = 0; i < sizeB; i++) {
        printf("%d ", arrayB[i]);
    }
    printf("\n");

    int* arrayC = (int*)malloc((long unsigned int)sizeA2 * sizeof(int));
    if (arrayC == NULL) {
        LogErrors(MEMORY_ALLOCATION_ERROR);
        free(arrayA2);
        free(arrayB);
        return 1;
    }

    err = findNearestValue(arrayA2, sizeA2, arrayB, sizeB, arrayC);
    if (findNearestValue(arrayA2, sizeA2, arrayB, sizeB, arrayC) != OK) {
        LogErrors(err);
        free(arrayA2);
        free(arrayB);
        free(arrayC);
        return 1;
    }

    printf("Array C (A[i] + nearest value from B):\n");
    for (size_t i = 0; i < sizeA2; i++) {
        printf("%d ", arrayC[i]);
    }
    printf("\n");

    free(arrayA2);
    free(arrayB);
    free(arrayC);

    return 0;
}
