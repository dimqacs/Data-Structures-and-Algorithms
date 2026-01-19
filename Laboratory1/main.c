#include <stdbool.h>

#include "../menu.h"
#include "array.h"

int main(void) {
    unsigned int option, arraySize = 0;
    int *array = NULL;

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

        printf("Introduce an option: ");

        if (scanf("%u", &option) != 1) { // NOLINT
            handleNext("Invalid Input.");
            continue;
        }

        switch (option) {
            case 1:
                displayArray(array, arraySize);
                break;
            case 2:
                arraySize = getArraySize();
                if (arraySize == 0) {
                    break;
                }
                fillArrayManually(&array, arraySize);
                break;
            case 3:
                // arraySize = getArraySize();
                // fillArrayRandomly(&array, arraySize);
                break;
            case 4:
                // sortArray();
                break;
            case 5:
                free(array);
                displayByeMessageAndExit();
            default:
                clearBuffer();
                handleNext("Invalid Option.");
                break;
        }
    }
}
