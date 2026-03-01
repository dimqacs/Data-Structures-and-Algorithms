#pragma once
#include <stdbool.h>

void displayMatrix(int *const *array, unsigned int size, const char *text, bool handleNextFlag);

unsigned int getMatrixSize();

bool allocateMatrixMemory(int ***array, unsigned int size);

void fillMatrixManually(int ***array, unsigned int size);

void fillMatrixRandomly(int ***array, unsigned int size);