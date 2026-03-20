#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array.h"
#include "menu.h"
#include "read.h"
#include "file.h"
#include "productArray.h"
#include "stack.h"

int main(void) {
    unsigned int option, stackSize = 0;

    Stack *stack = NULL;

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

    setMenuOptions(options, 15);

    printf("-------------------------Welcome-------------------------\n");

    while (true) { // NOLINT
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        switch (option) {
            case 1:
                readUnsignedInt("Enter the count of the Products that should be in Stack: ", &stackSize);

                if (stackSize == 0) {
                    handleNext("There can not be 0 Products in the Stack.");
                    break;
                }

                if (!allocateStackMemory(&stack, stackSize, sizeof(Product))) {
                    handleNext("Can not allocate Stack Memory.");
                    break;
                }

				fillProductArrayManually(stack->data, stackSize, false);

                clearTerminal();

                displayProductArray(stack->data, stackSize, "Products from the Stack:\n", true);

                break;
            case 9:
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
