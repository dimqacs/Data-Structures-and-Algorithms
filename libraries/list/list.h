#pragma once
#include <stdbool.h>

#include "menu.h"
#include "sort.h"

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t elementSize;
} List;

bool initializeList(List **list);

bool insertEnd(List *list, const void *element);

bool freeList(List *list);

void displayList(const List *list, display_t displayFunction, bool handleNextFlag);

bool allocateListMemory(List **list, size_t elementSize);

Node* getElementByIndex(const List *list, unsigned int elementIndex);

unsigned int getListLength(const List *list);

bool swapElements(const List *list, unsigned int firstElementIndex, unsigned int secondElementIndex);

void sortList(const List *list, compare_t compareFunction);