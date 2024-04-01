#include <stdio.h>
#include <stdlib.h>

// Create Node and Stack structures.
typedef struct Node {
    int data;
    struct Node *next;
} Node;
typedef struct Stack {
    Node *top;
    size_t size;
} Stack;

void initialize(Stack *const _stack) {
    _stack->top = (Node *)malloc(sizeof(Node));
    _stack->top->next = NULL;

    _stack->size = 0;
}
void push(Stack * const _stack, int const _data) {
    _stack->top->data  = _data;

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = _stack->top;
    _stack->top = newNode;

    ++_stack->size;
}
int pop(Stack *const _stack) {
    if(_stack->size == 0) {
        printf("\nUnderflow Error!\n");
        return -9995;
    }
    else {
        Node *toFree = _stack->top;
        _stack->top = _stack->top->next;
        free(toFree);
        --_stack->size;

        return _stack->top->data;
    }

}
void display(Stack const *const _stack){
    if(_stack->size  == 0) { 
        printf("\nStack is Empty.\n"); 
        return;
    }

    Node *toDisplay = _stack->top;
    printf("\nStack Elements: ");
    for(unsigned index  = 0; index < _stack->size; ++ index) {
        printf("%d->", toDisplay->next->data);
        toDisplay = toDisplay->next;
    }
    printf("X\n");
}
void cleanup(Stack *const _stack) {
    while(_stack->top != NULL){
        Node *toFree = _stack->top;
        _stack->top  = _stack->top->next;
        free(toFree);
    }
}

int main() {
  Stack stack;
    initialize(&stack);
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
        push(&stack, value);
        display(&stack);
        break;
      case 2:
        value = pop(&stack);
        if (value != -9995) {
          printf("Popped element: %d\n", value);
        }
        display(&stack);
        break;
      case 3:
        display(&stack);
        break;
      case 4:
        printf("\nExiting the program.\n");
        break;
      default:
        printf("\nInvalid choice. Please enter a valid option.\n");
      }
    } while (choice != 4);
    cleanup(&stack);

  return 0;
}
