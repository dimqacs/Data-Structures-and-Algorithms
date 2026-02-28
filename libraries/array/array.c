#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "read.h"
#include "menu.h"
#include "array.h"

void displayArray(const int *array, const unsigned int size, const char *text, const bool handleNextFlag) {
    if (size == 0) {
        handleNext("The array is empty, try introducing values first.");
        return;
    }

    text[0] == '\0' ? printf("The array with %u elements: ", size) : printf(text);

    for (int i = 0; i < size; i++) {
        printf("%d ", *(array + i));
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

unsigned int getArraySize() {
    unsigned int size;

    readUnsignedInt("Enter the size of the array: ", &size);

    return size;
}

bool allocateArrayMemory(int **array, const unsigned int size) {
    if (*array) {
        free(*array);
    }

    *array = calloc(size, sizeof(int));

    if (!*array) {
        handleNext("Memory allocation failed.");
        return false;
    }

    return true;
}

void fillArrayManually(int **array, const unsigned int size) {
    if (!allocateArrayMemory(array, size)) {
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Introduce the %u value: ", i + 1);

        readInt(prompt, *array + i);
    }

    displayArray(*array, size, "", true);
}

int getRandomNumber(const int min, const int max) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long milliseconds = ts.tv_nsec + ts.tv_sec * 1000000;

    // Linear Congruential Generator (LCG) https://en.wikipedia.org/wiki/Linear_congruential_generator
    milliseconds = (milliseconds * 214013 + 2531011) % 2147483648;

    const int range = max - min + 1;

    return (int) (milliseconds % range + range) % range + min;
}

void fillArrayRandomly(int **array, const int size) {
    if (!allocateArrayMemory(array, size)) {
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        *(*array + i) = getRandomNumber(-size, size);
    }

    displayArray(*array, size, "", true);
}

void equalArrays(const int *arrayFrom, int *arrayTo, const unsigned int size) {
    for (int index = 0; index < size; index++) {
        *(arrayTo + index) = *(arrayFrom + index);
    }
}

void swap(int *valueFrom, int *valueTo) {
    const int temp = *valueFrom;
    *valueFrom = *valueTo;
    *valueTo = temp;
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
