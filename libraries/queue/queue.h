#pragma once
#include <stdbool.h>
#include "menu.h"

typedef struct {
    void *data;
    unsigned int front;
    unsigned int rear;
    unsigned int size;
    size_t elementSize;
} Queue;

bool initQueue(Queue **queue);

bool enqueue(Queue *queue, const void *element);

bool freeQueue(Queue *queue);

void displayQueue(const Queue *queue, display_t displayFunction, bool handleNextFlag);

bool allocateQueueMemory(Queue **queue, unsigned int count, size_t elementSize);
