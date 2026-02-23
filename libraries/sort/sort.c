#include <stdlib.h>
#include <stdbool.h>

#include "sort.h"

#include <stdio.h>

#include "array.h"
#include "../array/array.h"

void heapify(int **array, const unsigned int size, const int index){

    // Initialize largest as root
    int largest = index;

    // left index = 2*i + 1
    const int left = 2 * index + 1;

    // right index = 2*i + 2
    const int right = 2 * index + 2;

    // If left child is larger than root
    if (left < size && *(*array + left) > *(*array + largest)) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < size && *(*array + right) > *(*array + largest)) {
        largest = right;
    }

    // If largest is not root
    if (largest != index) {
        const int temp = *(*array + index);
        *(*array + index) = *(*array + largest);
        *(*array + largest) = temp;

        // Recursively heapify the affected subtree
        heapify(array, size, largest);
    }
}

void heapSortAscending(int **array, const unsigned int size){

    // Build heap (rearrange vector)
    for (int index = size / 2 - 1; index >= 0; index--) {
        heapify(array, size, index);
    }

    // One by one extract an element from heap
    for (int index = size - 1; index > 0; index--) {

        // Move current root to end
        const int temp = **array;
        **array = *(*array + index);
        *(*array + index) = temp;

        // Call max heapify on the reduced heap
        heapify(array, index, 0);
    }

    printf("Array was sorted Ascending using Heap Sort.\n");
}

void countSortDescending(int **array, const unsigned int size) {

    // Find maximum and minimum element
    int maxValue = *(*array);
    int minValue = *(*array);
    for (int i = 0; i < size; i++) {
        const int value = *(*array + i);
        if (value > maxValue) maxValue = value;
        if (value < minValue) minValue = value;
    }

    const int range = maxValue - minValue + 1;

    // Create and initialize countArray array
    int *countArrayData = NULL;
    int **countArray = &countArrayData;
    allocateArrayMemory(countArray, range);

    // Count frequency of each element with shift
    for (int index = 0; index < size; index++) {
        (*(*countArray + (*(*array + index) - minValue)))++;
    }

    // Compute prefix sum
    for (int index = 1; index < range; index++) {
        *(*countArray + index) += *(*countArray + (index - 1));
    }

    // Build output array
    int* sortedArrayData = NULL;
    int** sortedArray = &sortedArrayData;
    allocateArrayMemory(sortedArray, size);

    for (int index = size - 1; index >= 0; index--) {
        const int value = *(*array + index);
        const int position = size - *(*countArray + (value - minValue));
        *(*sortedArray + position) = value;
        (*(*countArray + (value - minValue)))--;
    }

    // Copy sorted elements back to arr[]
    for (int index = 0; index < size; index++) {
        *(*array + index) = *(*sortedArray + index);
    }

    // Free dynamically allocated memory
    free(countArrayData);
    free(sortedArrayData);

    printf("Array was sorted Descending using Count Sort.\n");
}