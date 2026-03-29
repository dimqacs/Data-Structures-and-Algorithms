#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "menu.h"

bool initStack(Stack **stack) {
    if (*stack == NULL) {
        *stack = calloc(1, sizeof(Stack));
        if (!*stack) {
            return false;
        }
    }

    return true;
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

bool pop(Stack *stack) {
    if (stack->top == 0) {
        return false;
    }

    stack->top--;

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
    if (!stack || !stack->data) {
        return false;
    }

    free(stack->data);

    stack->data = NULL;
    stack->top = 0;

    return true;
}

void displayStack(const Stack *stack, display_t displayFunction, const bool handleNextFlag) {
    for (int index = (int)stack->top - 1; index >= 0; index--) {
        const void *element = (const char *) stack->data + index * stack->elementSize;
        displayFunction(element);
    }

    if (handleNextFlag) {
        handleNext("");
    }
}

bool allocateStackMemory(Stack **stack, const unsigned int count, const size_t elementSize) {
    if (!initStack(stack)) {
        return false;
    }

    void *tmp = calloc(count, elementSize);

    if (!tmp) {
        return false;
    }

    free((*stack)->data);

    (*stack)->data = tmp;
	(*stack)->top = 0;
    (*stack)->elementSize = elementSize;

    return true;
}