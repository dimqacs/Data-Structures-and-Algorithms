#include <stdlib.h>

#include "queue.h"

#include <stdio.h>
#include <string.h>

#include "menu.h"

bool initQueue(Queue **queue) {
    if (*queue == NULL) {
        *queue = calloc(1, sizeof(Queue));
        if (!*queue) {
            return false;
        }
    }

    return true;
}

bool freeQueue(Queue *queue) {
    if (!queue || !queue->data) {
        return false;
    }

    free(queue->data);

    queue->data = NULL;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;

    return true;
}

bool enqueue(Queue *queue, const void *element) {
    void *tmp = realloc(queue->data, (queue->size + 1) * queue->elementSize);

    if (!tmp) {
        return false;
    }

    queue->data = tmp;
    memcpy((char *)queue->data + queue->size * queue->elementSize, element, queue->elementSize);
    queue->size++;
    queue->rear = queue->size - 1;

    return true;
}

void displayQueue(const Queue *queue, display_t displayFunction, const bool handleNextFlag) {
    for (unsigned int index = queue->front; index <= queue->rear; index++) {
        const void *element = (const char *) queue->data + index * queue->elementSize;
        displayFunction(element);
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

bool allocateQueueMemory(Queue **queue, const unsigned int count, const size_t elementSize) {
    if (!initQueue(queue)) {
        return false;
    }

    void *tmp = calloc(count, elementSize);

    if (!tmp) {
        return false;
    }

    free((*queue)->data);

    (*queue)->data = tmp;
    (*queue)->front = 0;
    (*queue)->rear = -1;
    (*queue)->size = 0;
    (*queue)->elementSize = elementSize;

    return true;
}