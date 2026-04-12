#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array.h"
#include "menu.h"
#include "read.h"
#include "sort.h"
#include "file.h"
#include "productArray.h"

int main(void) {
    unsigned int option, arraySize = 0, productIndex = 0;

    Product *array = NULL, product;

    const char filePath[] = "./Laboratory3/products";

    const char *options[] = {
        "Create new File and fill it with Products",
        "Display Products from File",
        "Add new Product to the end of the File",
        "Edit a Product from File",
        "Search a Product from File by ArticleID",
        "Sort Products from File by Price",
        "Delete a Product from the File",
        "Delete File from the System",
        "-------------------------------------------------------",
        "Free Space & Exit",
        "-------------------------------------------------------"
    };

    setMenuOptions(options, 11);

    printf("-------------------------Welcome-------------------------\n");

    while (true) { // NOLINT
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        arraySize = 0;

        switch (option) {
            case 1:
                if (!createFile(filePath)) {
                    handleNext("File already exists, you need to delete it before creating a new one.");
                    break;
                }

                readUnsignedInt("Enter the count of the Products: ", &arraySize);

                if (arraySize == 0) {
                    handleNext("There can not be 0 Products in File.");
                    deleteFile(filePath);
                    break;
                }

                if (!allocateArrayMemory((void **) &array, arraySize, sizeof(Product))) {
                    break;
                }

                fillProductArrayManually(array, arraySize, false);

                if (!writeArrayToFile(filePath, array, arraySize, sizeof(Product), "r+b")) {
                    handleNext("Can not open the file for write. Make sure the file exists.");
                    break;
                }

                free(array);
                array = NULL;

                handleNext("File successfully created and filled with the provided Products.");
                break;
            case 2:
                array = readArrayFromFile(filePath, &arraySize, sizeof(Product));

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                displayProductArray(array, arraySize, "Products from file: \n",true);

                free(array);
                array = NULL;

                break;
            case 3:
                if (!fileExists(filePath)) {
                    handleNext("File doesn't exist, try creating it first.");
                    break;
                }

                printf("\nIntroduce information of new Product: \n");
                product = readNewProduct();

                if (!writeArrayToFile(filePath, &product, 1, sizeof(Product), "r+b")) {
                    handleNext("Can't open file to write. Some error occurred.");
                    break;
                }

                handleNext("New product has been successfully added to the File.");
                break;
            case 4:
                if (!fileExists(filePath)) {
                    handleNext("File with Products doesn't exist, try creating it first.");
                    break;
                }

                readUnsignedInt("Introduce the Index of the Product you want to Edit: ", &productIndex);

                array = readArrayFromFile(filePath, &arraySize, sizeof(Product));

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                if (productIndex > arraySize || productIndex == 0) {
                    handleNext("The is no Product with such index. Try introducing a correct index.");

                    free(array);
                    array = NULL;

                    break;
                }

                printf("\nIntroduce new Values for the Product with index %d:\n", productIndex);
                product = readNewProduct();

                *(array + productIndex - 1) = product;

                handleNext(
                    writeArrayToFile(filePath, array, arraySize, sizeof(Product), "wb")
                        ? "\nThe Product was successfully updated in the File.\n"
                        : "\nFailed to update the File. No changes were made.\n"
                );

                free(array);
                array = NULL;
                productIndex = 0;

                break;
            case 5:
                if (!fileExists(filePath)) {
                    handleNext("File with Products doesn't exist, try creating it first.");
                    break;
                }

                int articleId;
                readInt("Introduce the ArticleId of the Product you want to Search: ", &articleId);

                array = readArrayFromFile(filePath, &arraySize, sizeof(Product));

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                bool found = false;

                for (unsigned int index = 0; index < arraySize; index++) {
                    if ((array + index)->articleID == articleId) {
                        product = *(array + index);
                        found = true;
                        break;
                    }
                }

                free(array);
                array = NULL;

                if (!found) {
                    handleNext("There is no Product with the provided ArticleId");
                    break;
                }

                printf("\nFound Product with ArticleID %d:\n", articleId);\
                displayProduct(&product);

                handleNext("");
                break;
            case 6:
                if (!fileExists(filePath)) {
                    handleNext("File with Products doesn't exist, try creating it first.");
                    break;
                }

                array = readArrayFromFile(filePath, &arraySize, sizeof(Product));

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                if (!displayProductArray(array, arraySize, "\nUnsorted Products Array: \n", false)) {
                    free(array);
                    break;
                }

                displayProductArray(
                    quickSortAscending(array, arraySize, sizeof(Product), compareProductsByPrice),
                    arraySize,
                    "\nSorted Products Array Ascending based on Price field using Quick Sort:\n",
                    false
                );

                displayProductArray(
                    bubbleSortDescending(array, arraySize, sizeof(Product), compareProductsByPrice),
                    arraySize,
                    "\nSorted Products Array Descending based on Price field using Bubble Sort:\n",
                    false
                );

                free(array);
                array = NULL;

                handleNext("");

                break;
            case 7:
                if (!fileExists(filePath)) {
                    handleNext("File with Products doesn't exist, try creating it first.");
                    break;
                }

                readUnsignedInt("Introduce the Index of the Product you want to Delete: ", &productIndex);

                array = readArrayFromFile(filePath, &arraySize, sizeof(Product));

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                if (productIndex > arraySize || productIndex == 0) {
                    handleNext("The is no Product with such index. Try introducing a correct index.");

                    free(array);
                    array = NULL;

                    break;
                }

                arraySize--;

                handleNext(
                    writeArrayToFile(filePath,
                                     removeElement(array, arraySize, --productIndex, sizeof(Product)),
                                     arraySize,
                                     sizeof(Product),
                                     "wb"
                    )
                        ? "\nThe Product was successfully deleted from the File.\n"
                        : "\nFailed to delete product from the File. No changes were made.\n"
                );

                free(array);
                array = NULL;
                productIndex = 0;

                break;
            case 8:
                handleNext(deleteFile(filePath)
                               ? "\nFile was successfully deleted.\n"
                               : "\nThere is nothing to delete. \n"
                );

                break;
            case 9:
                free(array);
                printf("Memory cleaned successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
