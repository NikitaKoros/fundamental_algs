#include "util_task9.h"

const char* ErrorToString(const Error error) {
    switch (error) {
        case MEMORY_ALLOCATION_ERROR:
            return "MEMORY_ALLOCATION_ERROR";
        case WRONG_NUMBER_OF_PARAMETERS:
            return "WRONG_NUMBER_OF_PARAMETERS";
        case INVALID_BASE:
            return "INVALID_BASE";
        case INVALID_INPUT:
            return "INVALID_INPUT";
        default:
            return "UNKNOWN_ERROR";
    }
}

void LogErrors(Error err) {
    fprintf(stdout, "Error occured: %s\n", ErrorToString(err));
}

Error fillArray(int* array, size_t size, int min, int max) {
	if (array == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}
	srand((unsigned int)time(NULL));
	for (size_t i = 0; i < size; i++) {
		array[i] = min + rand() % (max - min + 1);
	}
	return OK;
}

void findAndSwapMinMax(int* array, size_t size) {
	if (array == NULL || size <= 0) return;

	int minIndex = 0, maxIndex = 0;
	for (size_t i = 1; i < size; i++) {
		if (array[i] < array[minIndex]) {
			minIndex = (int)i; //
		}
		if (array[i] > array[maxIndex]) {
			maxIndex = (int)i;
		}
	}

	int temp = array[minIndex];
	array[minIndex] = array[maxIndex];
	array[maxIndex] = temp;
}

int findNearest(int* arrayB, size_t sizeB, int target) {
	int left = 0, right = (int)sizeB - 1, mid;
	int nearest = arrayB[0];

	while (left <= right) {
		mid = left + (right - left) / 2;

		if (abs(arrayB[mid] - target) < abs(nearest - target)) {
			nearest = arrayB[mid];
		}

		if (arrayB[mid] < target) {
			left = mid + 1;
		} else if (arrayB[mid] > target) {
			right = mid - 1;
		} else {
			return arrayB[mid];
		}
	}

	return nearest;
}

Error findNearestValue(int* arrayA, size_t sizeA, int* arrayB, size_t sizeB, int* arrayC) {
	if (arrayA == NULL || arrayB == NULL || arrayC == NULL) {
		return MEMORY_ALLOCATION_ERROR;
	}

	qsort(arrayB, sizeB, sizeof(int), Comparator);

	for (size_t i = 0; i < sizeA; i++) {
		int nearest = findNearest(arrayB, sizeB, arrayA[i]);
		arrayC[i] = arrayA[i] + nearest;
	}

	return OK;
}

int Comparator(const void* a, const void* b) { return (*(int*)a - *(int*)b); }