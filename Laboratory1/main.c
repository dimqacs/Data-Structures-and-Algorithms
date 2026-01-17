#include <stdbool.h>

#include "./libraries/menu.h"

int main(void) {
    unsigned int option, count;
    int* array = NULL;

    printf("-------------------------Welcome-------------------------\n");

    while (true) {
        displayMenu();

        printf("Introduce an option: ");

        if (scanf("%u", &option) != 1) {
            handleError("Invalid Input. Try again.");
            continue;
        }

        switch (option) {
            case 1:
                // showArray();
                break;
            case 2:
                // array = fillArrayManually();
                break;
            case 3:
                // fillArrayRandomly();
                break;
            case 4:
                // sortArray();
                break;
            case 5:
                displayByeMessageAndExit();
            default:
                handleError("Invalid Option. Try again.");
                break;
        }

    }

    return 0;
}
