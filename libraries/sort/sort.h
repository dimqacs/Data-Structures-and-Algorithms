#pragma once

typedef int (*compare_t)(const void*, const void*);

int *heapSortAscending(const int *array, unsigned int size);

int *combSortAscending(const int *array, unsigned int size);

int *mergeSortAscending(const int *array, unsigned int size);

void *quickSortAscending(const void *array, unsigned int size, size_t elementSize, compare_t compare);

int *selectionSortAscending(const int *array, unsigned int size);

int *countSortDescending(const int *array, unsigned int size);

int *radixSortDescending(const int *array, unsigned int size);

void *bubbleSortDescending(const void *array, unsigned int size, size_t elementSize, compare_t compare);

int *shellSortDescending(const int *array, unsigned int size);

int *insertionSortDescending(const int *array, unsigned int size);
