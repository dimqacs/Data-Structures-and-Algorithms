#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "menu.h"
#include "read.h"
#include "productArray.h"

int main(void) {
    unsigned int option, listSize = 0, productIndex = 0;
    List *list = NULL;

    const char *options[] = {
        "-------------------------List-------------------------",
        "Create a new Dynamic List",
        "Fill the List manually",
        "Display List Information",
        "Search a product in the List",
        "Modify a product field in the List",
        "Get the Address of the Last Product",
        "Get List Length",
        "Swap Two Products by Index from the List",
        "Sort the List Ascending by Price",
        "Free List Memory",
        "-------------------------------------------------------",
        "Free Space & Exit",
        "-------------------------------------------------------"
    };

    setMenuOptions(options, 14);

    printf("-------------------------Welcome-------------------------\n");

    while (true) { // NOLINT
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        switch (option) {
            case 1:
                if (!allocateListMemory(&list, sizeof(Product))) {
                    handleNext("Failed to allocate List memory. Try again.");
                }

                handleNext("List structure initialized in dynamic memory.");

                break;
            case 2:
                if (!list) {
                    handleNext("List is not found. Try initializing the List first.");
                    break;
                }

                readUnsignedInt("Enter the count of the Products that should be in the List: ", &listSize);

                for (unsigned int index = 0; index < listSize; index++) {
                    printf("\nProduct %d:\n", index + 1);
                    Product product = readNewProduct();
                    insertEnd(list, &product);
                }

                printf("Products from the List:\n");
                displayList(list, displayProduct, true);

                break;
            case 3:
                if (!list || !list->head) {
                    handleNext("List is empty or not initialised.");
                    break;
                }

                printf("Products from the List:\n");
                displayList(list, displayProduct, true);

                break;
            case 4:
                if (!list || !list->head) {
                    handleNext("List is empty or not initialised.");
                    break;
                }

                readUnsignedInt("Introduce the Index of the Product you want to Find: ", &productIndex);

                Node *foundNode = getElementByIndex(list, productIndex);

                if (!foundNode) {
                    handleNext("There is no Product with such index.");
                    break;
                }

                printf("\nFound Product at index %u:\n", productIndex);
                displayProduct(foundNode->data);

                handleNext("");
                break;
            case 5:
                if (!list || !list->head) {
                    handleNext("List is empty or not initialised.");
                    break;
                }

                readUnsignedInt("Introduce the Index of the Product you want to Edit: ", &productIndex);

                Node *targetNode = getElementByIndex(list, productIndex);

                if (!targetNode) {
                    handleNext("There is no Product with such index.");
                    break;
                }

                printf("\nIntroduce new Values for the Product at index %u:\n", productIndex);
                Product updatedProduct = readNewProduct();

                memcpy(targetNode->data, &updatedProduct, list->elementSize);

                printf("\nUpdated products from the List:\n");
                displayList(list, displayProduct, true);

                break;
            case 6:
                if (!list || !list->head) {
                    handleNext("List is empty or not initialised.");
                    break;
                }

                Node *temp = list->head;
                while (temp->next) {
                    temp = temp->next;
                }

                printf("The Address of the last element is: %p\n", (void *) temp);
                handleNext("");

                break;
            case 7:
                if (!list || !list->head) {
                    handleNext("List is empty or not initialised.");
                    break;
                }

                printf("Current List length is %u elements.\n", getListLength(list));

                handleNext("");
                break;
            case 8:
                if (!list || getListLength(list) < 2) {
                    handleNext("List must have at least 2 elements to swap.");
                    break;
                }

                unsigned int firstElementIndex, secondElementIndex;
                readUnsignedInt("Introduce index of first element: ", &firstElementIndex);
                readUnsignedInt("Introduce index of second element: ", &secondElementIndex);

                if (!swapElements(list, firstElementIndex, secondElementIndex)) {
                    handleNext("Invalid indices provided.");
                }

                printf("\nProducts after swap:\n");
                displayList(list, displayProduct, true);

                break;
            case 9:
                if (!list || !list->head) {
                    handleNext("List is empty or not initialised.");
                    break;
                }

                sortList(list, compareProductsByPrice);

                printf("\nList successfully sorted Ascending by Product Prices:\n");
                displayList(list, displayProduct, true);

                break;
            case 10:
                handleNext(
                    freeList(list)
                    ? "List memory successfully cleared."
                    : "There is nothing to clear."
                );

                break;
            case 11:
                if (freeList(list)) {
                    printf("Memory cleaned successfully. \n");
                }

                displayByeMessageAndExit();
                break;
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
