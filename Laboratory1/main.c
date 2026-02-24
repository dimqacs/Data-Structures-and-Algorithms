#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h"
#include "array.h"
#include "read.h"
#include "sort.h"

int main(void) {
    unsigned int option, arraySize = 0;
    int *arrayData = NULL;

    const char *options[] = {
        "Display Array",
        "Fill Array Manually",
        "Fill Array Randomly",
        "Sort Array",
        "Free Space & Exit"
    };

    setMenuOptions(options, 5);

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
                    handleNext("Cannot create array with size 0 or odd number of elements.");
                    break;
                }
                fillArrayManually(&arrayData, arraySize);
                break;
            case 3:
                arraySize = getArraySize();
                if (arraySize == 0 || arraySize % 2 == 1) {
                    handleNext("Cannot create array with size 0 or odd number of elements.");
                    break;
                }
                fillArrayRandomly(&arrayData, (int) arraySize);
                break;
            case 4:
                displayArray(arrayData, arraySize, "The original unsorted Array: ", false);

                bool sorted = false;

                for (int index = 0; index < arraySize; index++) {
                    if (*(arrayData + index) < 0 ) {
                        if (index % 2 == 0) {
                            displayArray(heapSortAscending(arrayData, arraySize), arraySize, "\nA: Ascending sorted Array using Heap Sort: ", false);
                            sorted = true;
                        }
                        break;
                    }
                }

                if (!sorted) {
                    displayArray(countSortDescending(arrayData, arraySize), arraySize, "\nA: Descending sorted Array using Count Sort: ", false);
                }

                handleNext("\nTemporary...");
                break;
            case 5:
                free(arrayData);
                printf("Memory cleaned successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
