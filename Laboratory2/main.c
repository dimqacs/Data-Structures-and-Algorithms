#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h"
#include "array.h"
#include "read.h"
#include "sort.h"
#include "math.h"
#include "productArray.h"

int main(void) {
    unsigned int option, arraySize = 0;

    Product *array = NULL;

    const char *options[] = {
        "Display Array",
        "Fill Array Manually",
        "Sort Array",
        "-------------------------------------------------------",
        "Free Space & Exit",
        "-------------------------------------------------------"
    };

    setMenuOptions(options, 6);

    printf("-------------------------Welcome-------------------------\n");

    while (true) { // NOLINT
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        switch (option) {
            case 1:
                displayProductArray(array, arraySize, "The Array with Products: \n", true);
                break;
            case 2:
                readUnsignedInt("Enter the size of the Array: ", &arraySize);

                if (arraySize == 0) {
                    handleNext("Cannot create Array with size 0");
                    break;
                }

                fillProductArrayManually(&array, arraySize);
                break;
            case 3:

            case 4:
                free(array);
                printf("Memory cleaned successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
