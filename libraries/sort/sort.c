#include <stdlib.h>
#include <stdio.h>

#include "sort.h"
#include "array.h"

void heapify(int *array, const unsigned int size, const int index) {
    // Initialize largest as root
    int largest = index;

    // left index = 2*i + 1
    const int left = 2 * index + 1;

    // right index = 2*i + 2
    const int right = 2 * index + 2;

    // If left child is larger than root
    if (left < size && *(array + left) > *(array + largest)) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < size && *(array + right) > *(array + largest)) {
        largest = right;
    }

    // If largest is not root
    if (largest != index) {
        const int temp = *(array + index);
        *(array + index) = *(array + largest);
        *(array + largest) = temp;

        // Recursively heapify the affected subtree
        heapify(array, size, largest);
    }
}

int *heapSortAscending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);

    equalArrays(array, sortedArray, size);

    // Build heap (rearrange vector)
    for (int index = (int) size / 2 - 1; index >= 0; index--) {
        heapify(sortedArray, size, index);
    }

    // One by one extract an element from heap
    for (int index = (int) size - 1; index > 0; index--) {
        // Move current root to end
        swap(sortedArray, sortedArray + index);

        // Call max heapify on the reduced heap
        heapify(sortedArray, index, 0);
    }

    return sortedArray;
}

int *countSortDescending(const int *array, const unsigned int size) {
    // Find maximum and minimum element
    int maxValue = *array;
    int minValue = *array;
    for (int i = 0; i < size; i++) {
        const int value = *(array + i);
        if (value > maxValue) maxValue = value;
        if (value < minValue) minValue = value;
    }

    const int range = maxValue - minValue + 1;

    // Create and initialize countArray array
    int *countArray = NULL;
    allocateArrayMemory(&countArray, range);

    // Count frequency of each element with shift
    for (int index = 0; index < size; index++) {
        (*(countArray + (*(array + index) - minValue)))++;
    }

    // Compute prefix sum
    for (int index = 1; index < range; index++) {
        *(countArray + index) += *(countArray + (index - 1));
    }

    // Build output array

    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);

    for (int index = (int) size - 1; index >= 0; index--) {
        const int value = *(array + index);
        const int position = (int) size - *(countArray + (value - minValue));
        *(sortedArray + position) = value;
        (*(countArray + (value - minValue)))--;
    }

    // Free dynamically allocated memory
    free(countArray);

    return sortedArray;
}

void countingSortDescending(int *array, const unsigned int size, const int exponent, const int minValue) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);

    int *countArray = NULL;
    allocateArrayMemory(&countArray, 10);

    // Store count of occurrences in count[]
    for (int index = 0; index < size; index++) {
        (*(countArray + ((*(array + index) - minValue) / exponent % 10)))++;
    }

    // Change count[index] so that count[index] now
    // contains actual position of this digit
    // in sorted array
    for (int index = 8; index >= 0; index--) {
        *(countArray + index) += *(countArray + index + 1);
    }

    // Build the sorted array
    for (int index = (int) size - 1; index >= 0; index--) {
        *(sortedArray + (*(countArray + ((*(array + index) - minValue) / exponent % 10)) - 1)) = *(array + index);
        (*(countArray + ((*(array + index) - minValue) / exponent % 10)))--;
    }

    // Copy the sorted array to original array,
    // so that original array now contains sorted
    // numbers according to current digit
    equalArrays(sortedArray, array, size);

    // Free dynamically allocated memory
    free(sortedArray);
    free(countArray);
}

int *radixSortDescending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);

    equalArrays(array, sortedArray, size);

    int maxValue = *array;
    int minValue = *array;
    for (int i = 0; i < size; i++) {
        const int value = *(array + i);
        if (value > maxValue) maxValue = value;
        if (value < minValue) minValue = value;
    }

    // Do counting sort for every digit
    // exponent is 10^index
    // where index is the current digit number
    for (int exponent = 1; (maxValue - minValue) / exponent > 0; exponent *= 10) {
        countingSortDescending(sortedArray, size, exponent, minValue);
    }

    return sortedArray;
}

int getNextGap(int gap) {
    // Shrink gap by Shrink factor
    gap = gap * 10 / 13;

    return gap < 1 ? 1 : gap;
}

int *combSortAscending(const int *array, unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);

    equalArrays(array, sortedArray, size);

    // Initialize gap
    int gap = (int) size;

    // Initialize swapped as true to make sure that loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last iteration caused a swap
    while (gap != 1 || swapped == true) {
        // Find the next gap
        gap = getNextGap(gap);

        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;

        // Compare all elements with current gap
        for (int index = 0; index < size - gap; index++) {
            if (*(sortedArray + index) > *(sortedArray + (index + gap))) {
                swap(sortedArray + index, sortedArray + index + gap);
                swapped = true;
            }
        }
    }

    return sortedArray;
}

// Merges two subarrays of array.
// First subarray is array[left...middle]
// Second subarray is array[middle+1...right]
void merge(int *array, const int left, const int middle, const int right) {
    const int leftArrayCount = middle - left + 1;
    const int rightArrayCount = right - middle;

    // Create temp arrays
    int *leftArray = NULL;
    allocateArrayMemory(&leftArray, leftArrayCount);

    int *rightArray = NULL;
    allocateArrayMemory(&rightArray, rightArrayCount);

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int index = 0; index < leftArrayCount; index++) {
        *(leftArray + index) = *(array + left + index);
    }

    for (int index = 0; index < rightArrayCount; index++) {
        *(rightArray + index) = *(array + middle + 1 + index);
    }

    // Merge the temp arrays back into array[left...right]
    int leftIndex = 0;
    int rightIndex = 0;
    int arrayIndex = left;
    while (leftIndex < leftArrayCount && rightIndex < rightArrayCount) {
        if (*(leftArray + leftIndex) <= *(rightArray + rightIndex)) {
            *(array + arrayIndex) = *(leftArray + leftIndex);
            leftIndex++;
        } else {
            *(array + arrayIndex) = *(rightArray + rightIndex);
            rightIndex++;
        }
        arrayIndex++;
    }

    // Copy the remaining elements of leftArray[],
    // if there are any
    while (leftIndex < leftArrayCount) {
        *(array + arrayIndex) = *(leftArray + leftIndex);
        leftIndex++;
        arrayIndex++;
    }

    // Copy the remaining elements of rightArray[],
    // if there are any
    while (rightIndex < rightArrayCount) {
        *(array + arrayIndex) = *(rightArray + rightIndex);
        rightIndex++;
        arrayIndex++;
    }

    // Free dynamically allocated memory
    free(leftArray);
    free(rightArray);
}

void mergeSort(int *array, const int left, const int right) {
    if (left < right) {
        const int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

int *mergeSortAscending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);
    equalArrays(array, sortedArray, size);

    mergeSort(sortedArray, 0, (int) size - 1);

    return sortedArray;
}

int *bubbleSortDescending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);
    equalArrays(array, sortedArray, size);

    for (int index = 0; index < size - 1; index++) {
        bool swapped = false;
        for (int secondIndex = 0; secondIndex < size - index - 1; secondIndex++) {
            if (*(sortedArray + secondIndex) < *(sortedArray + secondIndex + 1)) {
                swap(sortedArray + secondIndex, sortedArray + (secondIndex + 1));
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }

    return sortedArray;
}

int partition(int *array, const int low, const int high) {
    // Choose the pivot
    const int pivot = *(array + high);

    // Index of smaller element and indicates
    // the right position of pivot found so far
    int index = low - 1;

    // Traverse array[low...high] and move all smaller
    // elements to the left side. Elements from low to
    // i are smaller after every iteration
    for (int j = low; j < high; j++) {

        if (*(array + j) >= pivot) {
            continue;
        }

        index++;
        swap(array + index, array + j);
    }

    // Move pivot after smaller elements and
    // return its position
    swap(array + (index + 1), array + high);
    return index + 1;
}

void quickSort(int *array, const int low, const int high) {
    if (low < high) {
        
        // partition return index of pivot
        const int part = partition(array, low, high);

        // recursion calls for smaller elements
        // and greater or equals elements
        quickSort(array, low, part - 1);
        quickSort(array, part + 1, high);
    }
}

int *quickSortAscending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);
    equalArrays(array, sortedArray, size);
    
    quickSort(sortedArray, 0, (int)size - 1);
    
    return sortedArray;
}

int* shellSortDescending(const int* array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);
    equalArrays(array, sortedArray, size);

    // Start with a large gap, then reduce it step by step
    for (int gap = (int)size / 2; gap > 0; gap /= 2) {

        // Perform a "gapped" insertion sort for this gap size
        for (int index = gap; index < size; index++) {

            // Current element to be placed correctly
            const int temp = *(sortedArray + index);
            int j = index;

            // Shift elements that are smaller than temp to make space
            while (j >= gap && *(sortedArray + (j - gap)) < temp) {
                *(sortedArray + j) = *(sortedArray + (j - gap));
                j -= gap;
            }

            // Place temp in its correct location
            *(sortedArray + j) = temp;
        }
    }

    return sortedArray;
}

int *selectionSortAscending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);
    equalArrays(array, sortedArray, size);

    for (int index = 0; index < size - 1; index++) {

        // Assume the current position holds
        // the minimum element
        int minimum_index = index;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int secondIndex = index + 1; secondIndex < size; secondIndex++) {
            if (*(sortedArray + secondIndex) < *(sortedArray + minimum_index)) {
                // Update minimum_index if a smaller element is found
                minimum_index = secondIndex;
            }
        }

        // Move minimum element to its
        // correct position
        swap(sortedArray + minimum_index, sortedArray + index);
    }

    return sortedArray;
}

int *insertionSortDescending(const int *array, const unsigned int size) {
    int *sortedArray = NULL;
    allocateArrayMemory(&sortedArray, size);
    equalArrays(array, sortedArray, size);

    for (int index = 1; index < size; index++) {
        const int key = *(sortedArray + index);
        int secondIndex = index - 1;

        /* Move elements of array[0...index-1], that are
           greater than key, to one position ahead
           of their current position */
        while (secondIndex >= 0 && *(sortedArray + secondIndex) < key) {
            *(sortedArray + (secondIndex + 1)) = *(sortedArray + secondIndex);
            secondIndex--;
        }

        *(sortedArray + (secondIndex + 1)) = key;
    }

    return sortedArray;
}