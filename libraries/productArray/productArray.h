#pragma once
#include <stdbool.h>

typedef struct {
    char name[128];
    char country[64];
    char manufacturer[128];
    int articleID;
    float price;
} Product;

void displayProductArray(const Product *array, unsigned int size, const char *text, bool handleNextFlag);

void fillProductArrayManually(Product **array, unsigned int size);