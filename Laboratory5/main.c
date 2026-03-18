#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array.h"
#include "menu.h"
#include "read.h"
#include "file.h"
#include "productArray.h"

int main(void) {
    unsigned int option, arraySize = 0, productIndex = 0;

    Product *array = NULL, product;

    const char filePath[] = "./Laboratory4/products.csv";

    const char *options[] = {
        "-------------------------Stack-------------------------",
        "Create new Stack and fill it manually",
        "Export Stack to file stack.csv and stack.bin",
        "Find Stack maximum Product by Price",
        "Get Stack length",
        "Edit an Product from the Stack",
        "Add new Product to the end of the Stack",
        "Free space for Stack",
        "-------------------------Queue-------------------------",
        "Copy Stack products to Queue",
        "Export Queue to file queue.csv and queue.bin",
        "Free space for Queue",
        "-------------------------------------------------------",
        "Free Space & Exit",
        "-------------------------------------------------------"
    };

    setMenuOptions(options, 16);

    printf("-------------------------Welcome-------------------------\n");

    while (true) { // NOLINT
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        arraySize = 0;

        switch (option) {
            case 1:

                break;
            case 9:
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
