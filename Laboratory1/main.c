#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h"
#include "array.h"
#include "read.h"
#include "sort.h"
#include "math.h"

int main(void) {
    unsigned int option, arraySize = 0;
    int *arrayData = NULL;

    const char *options[] = {
        "-------------------------Array-------------------------",
        "Display Array",
        "Fill Array Manually",
        "Fill Array Randomly",
        "Sort Array",
        "-------------------------Matrix------------------------",
        "Display Matrix",
        "Fill Matrix Manually",
        "Fill Matrix Randomly",
        "Sort Matrix",
        "Sort Matrix",
        "-------------------------------------------------------",
        "Free Space & Exit",
        "-------------------------------------------------------"
    };

    setMenuOptions(options, 14);

    printf("-------------------------Welcome-------------------------\n");

    while (true) {
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        switch (option) {
            case 1:
                displayArray(arrayData, arraySize, "The original Array: ", true);
                break;
            case 2:
                arraySize = getArraySize();
                if (arraySize == 0 || arraySize % 2 == 1) {
                    arraySize = 0;
                    handleNext("Cannot create array with size 0 or odd number of elements.");
                    break;
                }
                fillArrayManually(&arrayData, arraySize);
                break;
            case 3:
                arraySize = getArraySize();
                if (arraySize == 0 || arraySize % 2 == 1) {
                    arraySize = 0;
                    handleNext("Cannot create array with size 0 or odd number of elements.");
                    break;
                }
                fillArrayRandomly(&arrayData, (int) arraySize);
                break;
            case 4:
                if (arraySize == 0) {
                    handleNext("There is nothing to sort, try adding Array first.");
                    break;
                }

                displayArray(arrayData, arraySize, "The original unsorted Array: ", false);

                // Condition A
                bool sorted = false;

                for (int index = 0; index < arraySize; index++) {
                    if (*(arrayData + index) < 0) {
                        if (index % 2 == 0) {
                            displayArray(heapSortAscending(arrayData, arraySize), arraySize,
                                         "\nA: First negative element is on even position - sorting the Array Ascending using Heap Sort: ", false);
                            sorted = true;
                        }
                        break;
                    }
                }

                if (!sorted) {
                    displayArray(countSortDescending(arrayData, arraySize), arraySize,
                                 "\nA: First negative element is not on even position - sorting the Array Descending using Count Sort: ", false);
                }

                // Condition B
                evenSmallerThenOdd(arrayData, arraySize)
                    ? displayArray(radixSortDescending(arrayData, arraySize), arraySize,
                                   "\nB: Sum of even elements is smaller then arithmetic mean of odd elements - sorting Array Descending using Radix Sort: ", false)
                    : displayArray(combSortAscending(arrayData, arraySize), arraySize,
                                   "\nB: Sum of even elements is not smaller then arithmetic mean of odd elements - sorting Array Ascending using Comb Sort: ", false);

                // Condition C
                unsigned int primeNumbers = 0;
                for (int index = 0; index < arraySize; index++) {
                    if (isPrime(*(arrayData + index))) {
                        primeNumbers++;
                    }
                }

                primeNumbers >= 2
                    ? displayArray(mergeSortAscending(arrayData, arraySize), arraySize,
                                   "\nC: There are minimum two prime numbers - sorting Ascending Array using Merge Sort: ", true)
                    : displayArray(bubbleSortDescending(arrayData, arraySize), arraySize,
                                   "\nC: There are less then two prime numbers - sorting Descending Array using Bubble Sort: ", true);

                break;
            case 5:
                displayArray(arrayData, arraySize, "The original Array: ", true);
                break;
            case 10:
                free(arrayData);
                printf("Memory cleaned successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
