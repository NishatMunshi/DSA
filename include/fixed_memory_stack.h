#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 100

typedef struct Stack
{
    int elements[STACKSIZE];
    int topPos;
} Stack;

void init_stack(Stack *const _stack)
{
    _stack->topPos = 0;
}
void stack_push(Stack *const _stack, int const _data)
{
    // check overflow
    if (_stack->topPos > STACKSIZE){
        printf("Overlow Error!\n");
        exit(1);
    }

    _stack->elements[_stack->topPos++] = _data;
}

void print_stack(Stack const *const _stack){
    if(_stack->topPos == 0){
        printf("Empty Stack\n");
        return;
    }
    printf("\nStack Elements:\n");
    for(unsigned index = 0; index < _stack->topPos;++index){
        printf("%d ", _stack->elements[index]);
    }
    printf("\n");
}

int stack_pop(Stack *const _stack)
{
    // check overflow
    if (_stack->topPos == 0){
        printf("Overlow Error!\n");
        exit(1);
    }

    int returnValue  = _stack->elements[--_stack->topPos];
    return returnValue;
}