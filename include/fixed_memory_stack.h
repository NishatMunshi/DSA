#pragma once

#include <stdlib.h> // for malloc
#include <assert.h> // for assert
#include <stdio.h>

typedef struct Fixed_Memory_Stack
{
    int *items;
    size_t top; // one after the top
    size_t capacity;
} Fixed_Memory_Stack;

Fixed_Memory_Stack *fmstack_create_stack(size_t const _maxSize)
{
    Fixed_Memory_Stack *stack = (Fixed_Memory_Stack *)malloc(sizeof(Fixed_Memory_Stack));

    stack->items = (int *)malloc(_maxSize * sizeof(int));
    stack->capacity = _maxSize;
    stack->top = 0;

    return stack;
}

void fmstack_push(Fixed_Memory_Stack *const _stack, int const _data)
{
    // check overflow
    assert(_stack->top < _stack->capacity);

    _stack->items[_stack->top++] = _data;
}

int fmstack_pop(Fixed_Memory_Stack *const _stack)
{
    // check underflow
    assert(_stack->top > 0);

    return _stack->items[--_stack->top];
}

void fmstack_display(Fixed_Memory_Stack const *const _stack)
{
    printf("Fixed Memory Stack: ");
    for (unsigned index = 0; index < _stack->top; ++index)
    {
        printf("%d ", _stack->items[index]);
    }
    printf("\n");
}