#ifndef DSA_STACK_DYNAMIC_H
#define DSA_STACK_DYNAMIC_H

typedef struct stack_dynamic_struct stack_dynamic;

stack_dynamic *stack_dynamic_create();
void           stack_dynamic_push(stack_dynamic *stack ,int data);
int            stack_dynamic_pop(stack_dynamic *stack);
void           stack_dynamic_display(stack_dynamic *stack);

#endif // DSA_STACK_DYNAMIC_H