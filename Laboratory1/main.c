#include <stdbool.h>

#include "../libraries/menu.h"
#include "../libraries/array.h"

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

        readUnsignedInt("Introduce an option: ", &option);

        switch (option) {
            case 1:
                displayArray(array, arraySize);
                break;
            case 2:
                arraySize = getArraySize();
                if (arraySize == 0) {
                    handleNext("Cannot create array with size 0.");
                    break;
                }
                fillArrayManually(&array, arraySize);
                break;
            case 3:
                arraySize = getArraySize();
                fillArrayRandomly(&array, (int) arraySize);
                break;
            case 4:
                // sortArray();
                break;
            case 5:
                free(array);
                printf("Memory cleaned successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
