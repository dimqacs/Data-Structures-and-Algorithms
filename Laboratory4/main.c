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

    const char filePath[] = "./Laboratory4/products.csv";

    const char *options[] = {
        "Create new Textual File and fill it with Products",
        "Display Products from Textual File",
        "Add new Product to the end of Textual File",
        "Edit a Product from Textual File",
        "Search a Product from Textual File by ArticleID",
        "Sort Products from Textual File by Price and Country",
        "Delete a Product from Textual File",
        "Delete Textual File from the System",
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

                if (!writeArrayToCSV(filePath, array, arraySize, sizeof(Product), "w", productSerializer, productCSVHeader)) {
                    handleNext("Can not open the file for write. Make sure the file exists.");
                    break;
                }

                free(array);
                array = NULL;

                handleNext("File successfully created and filled with the provided Products.");
                break;
            case 2:
                array = readArrayFromCSV(filePath, &arraySize, sizeof(Product), productDeserializer);

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

                if (!writeArrayToCSV(filePath, &product, 1, sizeof(Product), "a", productSerializer, NULL)) {
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

                array = readArrayFromCSV(filePath, &arraySize, sizeof(Product), productDeserializer);

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                if (productIndex > arraySize || productIndex == 0) {
                    handleNext("There is no Product with such index. Try introducing a correct index.");

                    free(array);
                    array = NULL;

                    break;
                }

                printf("\nIntroduce new Values for the Product with index %d:\n", productIndex);
                product = readNewProduct();

                *(array + productIndex - 1) = product;

                handleNext(
                    writeArrayToCSV(filePath, array, arraySize, sizeof(Product), "w", productSerializer,
                                    productCSVHeader)
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

                array = readArrayFromCSV(filePath, &arraySize, sizeof(Product), productDeserializer);

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

                array = readArrayFromCSV(filePath, &arraySize, sizeof(Product), productDeserializer);

                if (array == NULL) {
                    handleNext("Can not open the file for read. Make sure the file exists.");
                    break;
                }

                if (!displayProductArray(array, arraySize, "\nUnsorted Products Array: \n\n", false)) {
                    free(array);
                    break;
                }

                displayProductArray(
                    quickSortAscending(array, arraySize, sizeof(Product), compareProductsByPrice),
                    arraySize,
                    "\nSorted Products Array Ascending based on Price field using Quick Sort:\n\n",
                    false
                );

                displayProductArray(
                    bubbleSortDescending(array, arraySize, sizeof(Product), compareProductsByCountry),
                    arraySize,
                    "\nSorted Products Array Descending based on Country field using Bubble Sort:\n\n",
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

                array = readArrayFromCSV(filePath, &arraySize, sizeof(Product), productDeserializer);

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
                    writeArrayToCSV(filePath,
                                    removeElement(array, arraySize, --productIndex, sizeof(Product)),
                                    arraySize,
                                    sizeof(Product),
                                    "w",
                                    productSerializer,
                                    productCSVHeader
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
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
