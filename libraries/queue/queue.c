#include <stdlib.h>

#include "queue.h"
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