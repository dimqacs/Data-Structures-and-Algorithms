#pragma once
#include <stdbool.h>

void displayArray(const int *array, unsigned int size, const char *text, bool handleNextFlag);

unsigned int getArraySize();

bool allocateArrayMemory(int **array, unsigned int size);

void fillArrayManually(int **array, unsigned int size);

int getRandomNumber(int min, int max);

void fillArrayRandomly(int **array, int size);

void equalArrays(const int *arrayFrom, int *arrayTo, unsigned int size);

void swap(int *valueFrom, int *valueTo);

bool evenSmallerThenOdd(const int *array, unsigned int size);