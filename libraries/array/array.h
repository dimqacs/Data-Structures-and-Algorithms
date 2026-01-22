#pragma once

void displayArray(const int *array, const unsigned int size);

unsigned int getArraySize();

bool allocateArrayMemory(int **array, const unsigned int size);

void fillArrayManually(int **array, const unsigned int size);

int getRandomNumber(const int min, const int max);

void fillArrayRandomly(int **array, const int size);
