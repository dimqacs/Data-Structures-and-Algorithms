#pragma once
#include <stdbool.h>
#include "stack.h"
#include "queue.h"

typedef void (*serializer_t)(FILE*, const void*);
typedef void (*deserializer_t)(const char*, void*);
typedef void (*header_t)(FILE *);

bool createFile(const char *filename);

bool deleteFile(const char *filename);

bool writeArrayToFile(const char *filename, const void *array, unsigned int arraySize, size_t elementSize, const char *mode);

void *readArrayFromFile(const char *fileName, unsigned int *size, size_t elementSize);

bool fileExists(const char *filename);

bool writeArrayToCSV(const char *filename, const void *array, unsigned int size, size_t elementSize, const char *mode, serializer_t serializer, header_t writeHeader);

void *readArrayFromCSV(const char *filename, unsigned int *size, size_t elementSize, deserializer_t deserializer);

bool exportStackToFile(const char *filename, const Stack *stack, const char *mode);

bool exportStackToCSVFile(const char *filename, const Stack *stack, const char *mode, serializer_t serializer, header_t writeHeader);

bool exportQueueToFile(const char *filename, const Queue *queue, const char *mode);

bool exportQueueToCSVFile(const char *filename, const Queue *queue, const char *mode, serializer_t serializer, header_t writeHeader);