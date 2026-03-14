#pragma once
#include <stdbool.h>

void displayArray(const int *array, unsigned int size, const char *text, bool handleNextFlag);

bool allocateArrayMemory(void **array, unsigned int count, size_t elementSize);

void fillArrayManually(int **array, unsigned int size);

void fillArrayRandomly(int **array, int size);

void equalArrays(const void *arrayFrom, void *arrayTo, unsigned int count, size_t elementSize);

void swap(void *valueFrom, void *valueTo, size_t size);

bool evenSmallerThenOdd(const int *array, unsigned int size);

void *removeElement(const void *array, unsigned int count, unsigned int elementIndex, size_t elementSize);