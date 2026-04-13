#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "menu.h"
#include "math.h"
#include "matrix.h"

void displayMatrix(int *const *matrix, const unsigned int size, const char *text, const bool handleNextFlag) {
    if (size == 0) {
        handleNext("The Matrix is empty, try introducing values first.");
        return;
    }

    text[0] == '\0' ? printf("The Matrix with %ux%u elements: \n", size, size) : printf("%s", text);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%i ", *(*(matrix + i) + j));
        }

        printf("\n");
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

void freeMatrix(int ***matrix, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        free(*(*matrix + i));
    }
    free(*matrix);
}

bool allocateMatrixMemory(int ***matrix, const unsigned int newSize, const unsigned int oldSize) {
    if (*matrix) {
        freeMatrix(matrix, oldSize);
    }

    *matrix = calloc(newSize, sizeof(int *));
    if (!*matrix) {
        handleNext("Memory allocation failed.");
        return false;
    }

    for (unsigned int i = 0; i < newSize; i++) {
        *(*matrix + i) = calloc(newSize, sizeof(int));

        if (!*(*matrix + i)) {
            freeMatrix(matrix, i);

            handleNext("Memory allocation failed.");
            return false;
        }
    }

    return true;
}

void fillMatrixManually(int ***matrix, const unsigned int newSize, const unsigned int oldSize) {
    if (!allocateMatrixMemory(matrix, newSize, oldSize)) {
        return;
    }

    for (unsigned int i = 0; i < newSize; i++) {
        for (unsigned int j = 0; j < newSize; j++) {
            char prompt[64];
            snprintf(prompt, sizeof(prompt), "Introduce the %u value from the row %u: ", j, i);

            readInt(prompt, *(*matrix + i) + j);
        }
    }

    displayMatrix(*matrix, newSize, "", true);
}

void fillMatrixRandomly(int ***matrix, const unsigned int newSize, const unsigned int oldSize) {
    if (!allocateMatrixMemory(matrix, newSize, oldSize)) {
        return;
    }

    for (unsigned int i = 0; i < newSize; i++) {
        for (unsigned int j = 0; j < newSize; j++) {
            *(*(*matrix + i) + j) = getRandomNumber(-(int) newSize, (int) newSize);
        }
    }

    displayMatrix(*matrix, newSize, "", true);
}

void equalMatrix(int ***matrixFrom, int ***matrixTo, const unsigned int size) {
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            *(*(*matrixTo + row) + column) = *(*(*matrixFrom + row) + column);
        }
    }
}
