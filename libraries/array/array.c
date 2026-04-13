#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "read.h"
#include "menu.h"
#include "math.h"

void displayArray(const int *array, const unsigned int size, const char *text, const bool handleNextFlag) {
    if (size == 0) {
        handleNext("The Array is empty, try introducing values first.");
        return;
    }

    text[0] == '\0' ? printf("The Array with %u elements: ", size) : printf("%s", text);

    for (int i = 0; i < size; i++) {
        printf("%d ", *(array + i));
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

bool allocateArrayMemory(void **array, const unsigned int count, const size_t elementSize) {
    if (*array) {
        free(*array);
    }

    *array = calloc(count, elementSize);

    if (!*array) {
        handleNext("Memory allocation failed.");
        return false;
    }

    return true;
}

void fillArrayManually(int **array, const unsigned int size) {
    if (!allocateArrayMemory((void **) array, size, sizeof(int))) {
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Introduce the %u value: ", i);

        readInt(prompt, *array + i);
    }

    displayArray(*array, size, "", true);
}

void fillArrayRandomly(int **array, const int size) {
    if (!allocateArrayMemory((void **) array, size, sizeof(int))) {
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        *(*array + i) = getRandomNumber(-size, size);
    }

    displayArray(*array, size, "", true);
}

void equalArrays(const void *arrayFrom, void *arrayTo, const unsigned int count, const size_t elementSize) {
    memcpy(arrayTo, arrayFrom, count * elementSize);
}

void swap(void *valueFrom, void *valueTo, const size_t size) {
    char temp[size];
    memcpy(temp, valueFrom, size);
    memcpy(valueFrom, valueTo, size);
    memcpy(valueTo, temp, size);
}

bool evenSmallerThenOdd(const int *array, const unsigned int size) {
    double even = 0, odd = 0, oddCount = 0;

    for (unsigned int index = 0; index < size; index++) {
        if (*(array + index) % 2 == 0) {
            even += *(array + index);
        } else {
            odd += *(array + index);
            oddCount++;
        }
    }

    return even < odd / oddCount ? true : false;
}

void *removeElement(const void *array, const unsigned int count, const unsigned int elementIndex,
                    const size_t elementSize) {
    void *resultArray = NULL;
    if (!allocateArrayMemory(&resultArray, count, elementSize)) {
        return NULL;
    }

    unsigned int destIndex = 0;
    for (unsigned int srcIndex = 0; srcIndex < count + 1; srcIndex++) {
        if (elementIndex == srcIndex) {
            continue;
        }

        memcpy(resultArray + destIndex * elementSize, array + srcIndex * elementSize, elementSize);

        destIndex++;
    }

    return resultArray;
}
