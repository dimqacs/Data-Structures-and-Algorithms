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
                displayArray(arrayData, arraySize);
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
                fillArrayRandomly(&arrayData, (int) arraySize);
                break;
            case 4:
                if (arraySize == 0) {
                    handleNext("There is nothing to sort, try adding elements first.");
                    break;
                }

                for (int index = 0; index < arraySize; index++) {
                    if (*(arrayData + index) < 0) {
                        index % 2 == 0 ? heapSortAscending(&arrayData, arraySize) : countSortDescending(&arrayData, arraySize);
                        break;
                    }
                }

                displayArray(arrayData, arraySize);
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
