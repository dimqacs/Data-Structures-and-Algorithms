#pragma once
#include <stdio.h>
#include <time.h>

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
    clearBuffer();

    unsigned int size;

    printf("Enter the size of the array: ");

    if (scanf("%u", &size) != 1 || size == 0) { // NOLINT
        handleNext("Invalid size of the Array provided. No Array will be created.");
        return 0;
    }

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
        printf("Introduce the %u value: ", i + 1);
        scanf("%d", *array + i); //NOLINT
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
