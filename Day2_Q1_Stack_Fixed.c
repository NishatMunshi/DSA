#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100

typedef struct Stack
{
    int items[STACKSIZE];
    unsigned top;
} Stack;

void initialize(Stack *const _stack) { _stack->top = 0; }
int full(Stack const *const _stack) { return _stack->top == STACKSIZE; }
int empty(Stack const *const _stack) { return _stack->top == 0; }

void push(Stack *const _stack, int const _data) {
    if (full(_stack))
        printf("\nOverflow Error!\n");
    else
        _stack->items[_stack->top++] = _data;
}
int pop(Stack *const _stack) {
    if (empty(_stack)) {
        printf("\nUnderflow Error!\n");
        return -9995; // return a special value that can be identified later
    }
    return _stack->items[--_stack->top];
}
void display(Stack const *const _stack) {
    if (empty(_stack))
        printf("\nStack is Empty.\n");
    else {
        printf("\nStack Elements: ");
        for (unsigned index = 0; index < _stack->top; ++index) {
            printf("%d ", _stack->items[index]);
        }
        printf("\n");
    }
}

int main() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
        initialize(stack);
    int i, choice, value, testCases;
        do {
            printf("\nMenu:\n");
            printf("1. Push\n");
            printf("2. Pop\n");
            printf("3. Display\n");
            printf("4. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(stack, value);
                display(stack);
                break;
            case 2:
                value = pop(stack);
                if (value != -9995) 
                    printf("Popped element: %d\n", value);
                display(stack);
                break;
            case 3:
                display(stack);
                break;
            case 4:
                printf("\nExiting the program.\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
            }
        } while (choice != 4);
    return 0;
}
