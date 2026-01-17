#include <stdbool.h>

#include "./libraries/menu.h"
#include "./libraries/array.h"

int main(void) {
    unsigned int option, arraySize = 0;
    int *array = NULL;

    printf("-------------------------Welcome-------------------------\n");

    while (true) {
        displayMenu();

        printf("Introduce an option: ");

        if (scanf("%u", &option) != 1) { // NOLINT
            handleError("Invalid Input. Try again.");
            continue;
        }

        switch (option) {
            case 1:
                displayArray(array, arraySize);
                break;
            case 2:
                arraySize = getArraySize();
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
                handleError("Invalid Option. Try again.");
                break;
        }
    }
}
