#pragma once
#include <stdbool.h>

void displayMatrix(int *const *matrix, unsigned int size, const char *text, bool handleNextFlag);

bool allocateMatrixMemory(int ***matrix, unsigned int newSize, unsigned int oldSize);

void fillMatrixManually(int ***matrix, unsigned int newSize, unsigned int oldSize);

void fillMatrixRandomly(int ***matrix, int newSize, unsigned int oldSize);