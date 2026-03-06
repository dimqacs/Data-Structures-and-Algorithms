#pragma once
#include <stdbool.h>

void displayArray(const int *array, unsigned int size, const char *text, bool handleNextFlag);

bool allocateArrayMemory(void **array, size_t count, size_t elementSize);

void fillArrayManually(int **array, unsigned int size);

void fillArrayRandomly(int **array, int size);

void equalArrays(const int *arrayFrom, int *arrayTo, unsigned int size);

void swap(int *valueFrom, int *valueTo);

bool evenSmallerThenOdd(const int *array, unsigned int size);