#include <stdio.h>
#include <stdbool.h>

#include "productArray.h"

#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "read.h"
#include "menu.h"

Product readNewProduct() {
    Product product;

    printf("Introduce name: ");
    scanf(" %[^\n]", product.name);

    printf("Introduce country: ");
    scanf(" %[^\n]", product.country);

    printf("Introduce manufacturer: ");
    scanf(" %[^\n]", product.manufacturer);

    clearBuffer();

    readInt("Introduce articleID:", &product.articleID);

    readUnsignedFloat("Introduce price: ", &product.price);

    return product;
}

void displayProduct(const Product *product) {
    printf("  Name       : %s\n", product->name);
    printf("  Country    : %s\n", product->country);
    printf("  Manufacturer: %s\n", product->manufacturer);
    printf("  ArticleID  : %u (Hex: %X)\n", product->articleID, product->articleID);
    printf("  Price      : %.2f\n\n", product->price);
}

bool displayProductArray(const Product *array, const unsigned int size, const char *text, const bool handleNextFlag) {
    if (size == 0) {
        handleNext("The Array is empty, try introducing values first.");
        return false;
    }

    text[0] == '\0' ? printf("The Array with %u elements: ", size) : printf("%s", text);

    for (int index = 0; index < size; index++) {
        printf("Product %d:\n", index + 1);
        displayProduct(array + index);
    }

    if (handleNextFlag) {
        handleNext("");
    }

    return true;
}

void fillProductArrayManually(Product **array, const unsigned int size, const bool handleNextFlag) {
    if (!allocateArrayMemory((void **) array, size, sizeof(Product))) {
        return;
    }

    for (unsigned int index = 0; index < size; index++) {
        printf("\nIntroduce information of product number %d:\n", index + 1);
        *(*array + index) = readNewProduct();
    }

    displayProductArray(*array, size, "The Array with Products: \n", handleNextFlag ? true : false);
}

int compareProductsByPrice(const void *a, const void *b) {
    const Product *productA = a;
    const Product *productB = b;

    return productA->price > productB->price ? 1 : productA->price < productB->price ? -1 : 0;
}

int compareProductsByCountry(const void *a, const void *b) {
    const Product *productA = a;
    const Product *productB = b;

    return strcmp(productA->country, productB->country);
}

void productSerializer(FILE *file, const void *element) {
    const Product *product = element;

    fprintf(file, "%s,%s,%s,%u,%.2f\n",
            product->name,
            product->country,
            product->manufacturer,
            product->articleID,
            product->price);
}

void productDeserializer(const char *line, void *element) {
    Product *p = element;

    char articleIdString[32], priceIdString[32];

    sscanf(line, "%49[^,],%49[^,],%49[^,],%31[^,],%31s",
           p->name,
           p->country,
           p->manufacturer,
           articleIdString,
           priceIdString
    );

    p->articleID = (int) strtoul(articleIdString, NULL, 10);
    p->price = strtof(priceIdString, NULL);
}

void productCSVHeader(FILE *file) {
    fprintf(file, "name,country,manufacturer,articleId,price\n");
}