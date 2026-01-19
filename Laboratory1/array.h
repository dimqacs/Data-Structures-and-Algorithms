#pragma once
#include <stdio.h>

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

static void fillArrayManually(int **array, const unsigned int size) {
    if (*array) {
        free(*array);
    }

    *array = calloc(size, sizeof(int));

    if (!*array) {
        handleNext("Memory allocation failed.");
        return;
    }

    for (unsigned int i = 0; i < size; i++) {
        printf("Introduce the %u value: ", i + 1);
        scanf("%d", *array + i); //NOLINT
    }

    clearTerminal();
}
