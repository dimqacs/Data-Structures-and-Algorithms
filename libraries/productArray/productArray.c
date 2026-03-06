#include <stdio.h>
#include <stdbool.h>

#include "productArray.h"
#include "array.h"
#include "read.h"
#include "menu.h"

void displayProductArray(const Product *array, const unsigned int size, const char *text, const bool handleNextFlag){
    if (size == 0) {
        handleNext("The Array is empty, try introducing values first.");
        return;
    }

    text[0] == '\0' ? printf("The Array with %u elements: ", size) : printf("%s", text);

    for (int index = 0; index < size; index++) {
        printf("Product %d:\n", index + 1);
        printf("  Name       : %s\n", (array + index)->name);
        printf("  Country    : %s\n", (array + index)->country);
        printf("  Manufacturer: %s\n", (array + index)->manufacturer);
        printf("  ArticleID  : %u (Hex: %X)\n", (array + index)->articleID, (array + index)->articleID);
        printf("  Price      : %.2f\n\n", (array + index)->price);
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

void fillProductArrayManually(Product **array, const unsigned int size) {
    if (!allocateArrayMemory((void**)array, size, sizeof(Product))) {
        return;
    }

    for (unsigned int index = 0; index < size; index++) {
        Product product;

        printf("Introduce information of product number %d:\n", index + 1);

        printf("Introduce name: ");
        scanf(" %[^\n]", product.name);

        printf("Introduce country: ");
        scanf(" %[^\n]", product.country);

        printf("Introduce manufacturer: ");
        scanf(" %[^\n]", product.manufacturer);

        clearBuffer();

        readInt("Introduce articleID:", &product.articleID);

        readUnsignedFloat("Introduce price: ", &product.price);

        printf("\n");

        *(*array + index) = product;
    }

    displayProductArray(*array, size, "The Array with Products: \n", true);
}
