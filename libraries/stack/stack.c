#include "stack.h"

#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "read.h"

void initStack(Stack *stack, const size_t elementSize) {
    stack->data = NULL;
    stack->top = 0;
    stack->elementSize = elementSize;
}

bool push(Stack *stack, const void *element) {
    void *tmp = realloc(stack->data, (stack->top + 1) * stack->elementSize);

    if (tmp == NULL) {
        return false;
    }

    stack->data = tmp;

    memcpy((char *) stack->data + stack->top * stack->elementSize, element, stack->elementSize);

    stack->top++;

    return true;
}

bool pop(Stack *stack, void *element) {
    if (stack->top == 0) {
        return false;
    }

    stack->top--;

    memcpy(element, (char *) stack->data + stack->top * stack->elementSize, stack->elementSize);

    return true;
}

bool peek(const Stack *stack, void *element) {
    if (stack->top == 0) {
        return false;
    }

    memcpy(element, (char *) stack->data + (stack->top - 1) * stack->elementSize, stack->elementSize);

    return true;
}

bool freeStack(Stack *stack) {
    if (stack->top == 0 && stack->data == NULL) {
        return false;
    }

    free(stack->data);

    stack->data = NULL;
    stack->top = 0;

    return true;
}

void displayStack(const Stack *stack, const display_t displayFunction, const bool handleNextFlag) {
    for (unsigned int index = 0; index < stack->top; index++) {
        const void *element = (const char *) stack->data + index * stack->elementSize;
        displayFunction(element);
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

bool allocateStackMemory(Stack **stack, const unsigned int count, const size_t elementSize) {
    if (*stack == NULL) {
        initStack(*stack, elementSize);
    }

    if ((*stack)->top != 0) {
        freeStack(*stack);
    }

    void *tmp = calloc(count, (*stack)->elementSize);

    if (!tmp) {
        handleNext("Memory allocation failed.");
        return false;
    }

    (*stack)->data = tmp;
    (*stack)->top = 0;

    return true;
}