#include <stdlib.h>
#include <string.h>

#include "list.h"

#include "array.h"

bool initializeList(List **list) {
    if (*list == NULL) {
        *list = calloc(1, sizeof(List));
        if (!*list) {
            return false;
        }
    }

    return true;
}

bool allocateListMemory(List **list, const size_t elementSize) {
    if (!initializeList(list)) {
        return false;
    }

    (*list)->head = NULL;
    (*list)->elementSize = elementSize;

    return true;
}

bool insertEnd(List *list, const void *element) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        return false;
    }

    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, element, list->elementSize);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *temp = list->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return true;
}

void displayList(const List *list, display_t displayFunction, const bool handleNextFlag) {
    const Node *temp = list->head;

    while (temp) {
        displayFunction(temp->data);
        temp = temp->next;
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

unsigned int getListLength(const List *list) {
    unsigned int count = 0;
    const Node *temp = list->head;

    while (temp) {
        count++;
        temp = temp->next;
    }

    return count;
}

Node* getElementByIndex(const List *list, const unsigned int elementIndex) {
    if (elementIndex == 0) {
        return NULL;
    }

    Node *temp = list->head;
    unsigned int loopIndex = 1;

    while (temp && loopIndex < elementIndex) {
        temp = temp->next;
        loopIndex++;
    }

    return temp;
}

bool swapElements(const List *list, const unsigned int firstElementIndex, const unsigned int secondElementIndex) {
    if (firstElementIndex == secondElementIndex) {
        return true;
    }

    Node *node1 = getElementByIndex(list, firstElementIndex);
    Node *node2 = getElementByIndex(list, secondElementIndex);

    if (!node1 || !node2) {
        return false;
    }

    void *tempData = node1->data;
    node1->data = node2->data;
    node2->data = tempData;

    return true;
}

void sortList(const List *list, compare_t compareFunction) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }

    const unsigned int size = getListLength(list);
    const size_t elementSize = list->elementSize;

    void *tempArray = NULL;
    if (!allocateArrayMemory(&tempArray, size, elementSize)) {
        return;
    }

    const Node *current = list->head;
    for (unsigned int index = 0; index < size; index++) {
        swap((char *)tempArray + index * elementSize, current->data, elementSize);
        current = current->next;
    }

    void *sortedArray = quickSortAscending(tempArray, size, elementSize, compareFunction);

    current = list->head;
    for (unsigned int index = 0; index < size; index++) {
        swap(current->data, (char *)sortedArray + index * elementSize, elementSize);
        current = current->next;
    }

    free(tempArray);
    free(sortedArray);
}

bool freeList(List *list) {
    if (!list) {
        return false;
    }

    Node *current = list->head;

    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->head = NULL;

    return true;
}