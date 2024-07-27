#include "../include/stack_fixed.h"

#include <stdio.h>
#include <stdlib.h>

struct stack_fixed_struct {
    int *  items;
    size_t top;
    size_t capacity;
};

stack_fixed *stack_fixed_create(size_t capacity) {
    stack_fixed *stack = malloc(sizeof(struct stack_fixed_struct));
    stack->items = malloc(capacity * sizeof(stack->items[0]));
    stack->top = 0;
    stack->capacity = capacity;
    return stack;
}

void stack_fixed_push(stack_fixed *stack, int data) {
    if (stack->top >= stack->capacity) {
        printf("[STACK_FIXED ERROR]: stack overflow\n");
        return;
    }
    stack->items[stack->top++] = data;
}

int stack_fixed_pop(stack_fixed *stack) {
    if (stack->top == 0) {
        printf("[STACK_FIXED ERROR]: stack underflow\n");
        return -1;
    }
    return stack->items[--stack->top];
}

void stack_fixed_display(stack_fixed *stack) {
    printf(
        "[STACK_FIXED INFO]:\n"
        "       CAPACITY: %zu\n"
        "       SIZE:     %zu\n"
        "       CONTENTS: {",
        stack->capacity, stack->top);

    for (size_t i = 0; i < stack->top; ++i) {
        printf("%i%s", stack->items[i], i == stack->top - 1 ? "" : ", ");
    }
    printf("}\n");
}
