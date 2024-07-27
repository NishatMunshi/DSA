#include "../include/stack_dynamic.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_dynamic_node_struct {
    int data;
    struct stack_dynamic_node_struct *next;
} stack_dynamic_node;

struct stack_dynamic_struct {
    stack_dynamic_node *top;
    size_t size;
};

stack_dynamic *stack_dynamic_create() {
    stack_dynamic *stack = malloc(sizeof(struct stack_dynamic_struct));
    stack->top = NULL;
    return stack;
    stack->size = 0;
}
void stack_dynamic_push(stack_dynamic *stack, int data) {
    stack_dynamic_node *new_node = malloc(sizeof(struct stack_dynamic_node_struct));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}
int stack_dynamic_pop(stack_dynamic *stack) {
    if (stack->top == NULL) {
        printf("[STACK_DYNAMIC ERROR]: stack underflow\n");
        return -1;
    }
    stack_dynamic_node *old_top = stack->top;
    int data = old_top->data;
    stack->top = old_top->next;
    free(old_top);
    stack->size--;
    return data;
}
void stack_dynamic_display(stack_dynamic *stack) {
    printf(
        "[STACK_DYNAMIC INFO]:\n"
        "       SIZE:     %zu\n"
        "       CONTENTS: {",
        stack->size);
    for (stack_dynamic_node *node = stack->top; node != NULL; node = node->next) {
        printf("%i%s", node->data, node->next == NULL ? "" : ", ");
    } printf("}\n");
}