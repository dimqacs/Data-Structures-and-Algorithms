#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#include "file.h"

#include <stdlib.h>
#include <string.h>

#include "array.h"

bool createFile(const char *filename) {
    const int fileDescriptor = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0755);

    if (fileDescriptor == -1) {
        return false;
    }

    close(fileDescriptor);

    return true;
}

bool deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        return true;
    }

    return false;
}

bool writeArrayToFile(const char *filename, const void *array, const unsigned int arraySize, const size_t elementSize,
                      const char *mode) {
    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        return false;
    }

    fseek(file, 0, SEEK_END);
    fwrite(array, elementSize, arraySize, file);

    fclose(file);

    return true;
}

void *readArrayFromFile(const char *fileName, unsigned int *size, const size_t elementSize) {
    FILE *file = fopen(fileName, "rb");

    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    const long fileSize = ftell(file);
    rewind(file);

    *size = fileSize / elementSize;

    void *array = NULL;
    allocateArrayMemory(&array, *size, elementSize);

    fread(array, elementSize, *size, file);

    fclose(file);

    return array;
}

bool fileExists(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file) {
        fclose(file);
        return true;
    }

    return false;
}

bool writeArrayToCSV(const char *filename, const void *array, const unsigned int size, const size_t elementSize, const char *mode, const serializer_t serializer, const header_t writeHeader) {
    FILE *file = fopen(filename, mode);

    if (!file) {
        return false;
    }

    if (writeHeader) {
        writeHeader(file);
    }

    for (unsigned int index = 0; index < size; index++) {
        serializer(file, (char *) array + index * elementSize);
    }

    fclose(file);

    return true;
}

void *readArrayFromCSV(const char *filename, unsigned int *size, const size_t elementSize, const deserializer_t deserializer) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        return NULL;
    }

    char line[256];
    fgets(line, sizeof(line), file);

    void *array = NULL;
    unsigned int count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;

        void *tmp = realloc(array, (count + 1) * elementSize);

        if (!tmp) {
            free(array);
            fclose(file);
            return NULL;
        }

        array = tmp;

        deserializer(line, (char*)array + count * elementSize);
        count++;
    }

    fclose(file);
    *size = count;

    return array;
}