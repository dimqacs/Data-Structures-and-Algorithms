#pragma once
#include <stdbool.h>
#include "menu.h"

typedef struct {
    void *data;
    unsigned int top;
    size_t elementSize;
} Stack;

bool initStack(Stack **stack);

bool push(Stack *stack, const void *element);

bool pop(Stack *stack);

bool peek(const Stack *stack, void *element);

bool freeStack(Stack *stack);

void displayStack(const Stack *stack, display_t displayFunction, bool handleNextFlag);

bool allocateStackMemory(Stack **stack, unsigned int count, size_t elementSize);
