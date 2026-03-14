#pragma once
#include <stdbool.h>

bool createFile(const char *filename);

bool deleteFile(const char *filename);

bool writeArrayToFile(const char *filename, const void *array, unsigned int arraySize, size_t elementSize, const char *mode);

void *readArrayFromFile(const char *fileName, unsigned int *size, size_t elementSize);

bool fileExists(const char *filename);