#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h"
#include "read.h"
#include "file.h"
#include "productArray.h"
#include "stack.h"

int main(void) {
    unsigned int option, stackSize = 0;

    Stack *stack = NULL;
    Product* products;

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
        "Free All Space & Exit",
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

                for (unsigned int index = 0; index < stackSize; index++) {
                    printf("\nIntroduce information of product number %d:\n", index + 1);
                    const Product product = readNewProduct();
                    push(stack, &product);
                }

                printf("Products from the Stack:\n");
                displayStack(stack, displayProduct, true);

                break;
            case 2:
                if (!stack || stack->top <= 0) {
                    handleNext("There is nothing to export. Trying creating the Stack first.");
                    break;
                }

                if (!exportStackToFile("./Laboratory5/stack.bin", stack, "wb")) {
                    handleNext("Some error occurred. Couldn't write Stack to .bin file.");
                    break;
                }

                if (!exportStackToCSVFile("./Laboratory5/stack.csv", stack, "w", productSerializer, productCSVHeader)) {
                    handleNext("Some error occurred. Couldn't write Stack to .csv file.");
                    break;
                }

                handleNext("Stack data successfully exported to stack.bin and stack.csv files.");
                break;
            case 3:
                if (!stack || stack->top <= 0) {
                    handleNext("Stack is empty or doesn't exist. Try creating the Stack first.");
                    break;
                }

                products = stack->data;
                const Product *max = &products[stack->top - 1];

                for (int index = (int)stack->top - 2; index >= 0; index--) {
                    if (compareProductsByPrice(&products[index], max) > 0) {
                        max = &products[index];
                    }
                }

                printf("Product with the maximum price:\n");
                displayProduct(max);

                handleNext("");
                break;
            case 4:
                if (!stack || stack->top <= 0) {
                    handleNext("Stack is empty or doesn't exist. Trying creating the Stack first.");
                    break;
                }

                printf("Stack length is %u.", stack->top);
                handleNext("");
                break;
            case 5:
                if (!stack || stack->top <= 0) {
                    handleNext("Stack is empty or doesn't exist. Trying creating the Stack first.");
                    break;
                }

                unsigned int productIndex;
                readUnsignedInt("Introduce the Index of the Product you want to Edit: ", &productIndex);

                if (productIndex > stack->top || productIndex == 0) {
                    handleNext("There is no Product with such index. Try introducing a correct index.");
                    break;
                }

                printf("\nIntroduce new Values for the Product with index %d:\n", productIndex);
                const Product updatedProduct = readNewProduct();

                products = stack->data;
                products[productIndex - 1] = updatedProduct;

                printf("Updated products from the Stack:\n");
                displayStack(stack, displayProduct, true);

                break;
            case 6:
                if (!stack || stack->top <= 0) {
                    handleNext("Stack is empty or doesn't exist. Trying creating the Stack first.");
                    break;
                }

                printf("\nIntroduce information of the new product:\n");
                const Product newProduct = readNewProduct();
                push(stack, &newProduct);

                printf("Updated products from the Stack:\n");
                displayStack(stack, displayProduct, true);

                break;
            case 7:
                handleNext(
                    freeStack(stack)
                        ? "Stack memory cleared successfully"
                        : "There is nothing to clear, stack is not initialized."
                );

                break;
            case 11:
                freeStack(stack);
                printf("All memory cleared successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
