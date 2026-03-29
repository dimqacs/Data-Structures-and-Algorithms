#pragma once
#include <stdbool.h>

typedef struct {
    char name[128];
    char country[64];
    char manufacturer[128];
    int articleID;
    float price;
} Product;

Product readNewProduct();

void displayProduct(const void *element);

bool displayProductArray(const Product *array, unsigned int size, const char *text, bool handleNextFlag);

void fillProductArrayManually(Product *array, unsigned int size, bool handleNextFlag);

int compareProductsByPrice(const void *a, const void *b);

int compareProductsByCountry(const void *a, const void *b);

void productSerializer(FILE *file, const void *element);

void productDeserializer(const char *line, void *element);

void productCSVHeader(FILE *file);