#pragma once
#include <stdio.h>
#include <time.h>

#include "../libraries/read.h"

static void displayArray(const int *array, const unsigned int size) {
    if (size == 0) {
        handleNext("The array is empty, try introducing values first.");
        return;
    }

    printf("The array with %u elements: ", size);

    for (int i = 0; i < size; i++) {
        printf("%d ", *(array + i));
    }

    handleNext("");
}

static unsigned int getArraySize() {
    unsigned int size;

    readUnsignedInt("Enter the size of the array: ", &size);

    return size;
}

static bool allocateArrayMemory(int **array, const unsigned int size) {
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

static void fillArrayManually(int **array, const unsigned int size) {
    if (!allocateArrayMemory(array, size)) {
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Introduce the %u value: ", i + 1);

        readInt(prompt, *array + i);
    }

    clearTerminal();
}

static int getRandomNumber(const int min, const int max) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long milliseconds = ts.tv_nsec + ts.tv_sec * 1000000;

    // Linear Congruential Generator (LCG) https://en.wikipedia.org/wiki/Linear_congruential_generator
    milliseconds = (milliseconds * 214013 + 2531011) % 2147483648;

    const int range = max - min + 1;

    return (int) (milliseconds % range + range) % range + min;
}

static void fillArrayRandomly(int **array, const int size) {
    if (!allocateArrayMemory(array, size)) {
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        *(*array + i) = getRandomNumber(-size, size);
    }

    handleNext("Array successfully filled.");
}
