#ifndef DSA_STACK_FIXED_H
#define DSA_STACK_FIXED_H

#include <stddef.h>

typedef struct stack_fixed_struct stack_fixed;

stack_fixed *stack_fixed_create(size_t capacity);
void         stack_fixed_push( stack_fixed *stack ,int data);
int          stack_fixed_pop(stack_fixed *stack);
void         stack_fixed_display(stack_fixed *stack);

#endif // DSA_STACK_FIXED_H