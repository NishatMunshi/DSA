#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *head, *tail;
  unsigned size;
} Queue;

void initialize(Queue *const _queue) {
  _queue->head = (Node *)malloc(sizeof(Node));
  _queue->head->next = (Node *)malloc(sizeof(Node));
  _queue->tail = _queue->head->next;
  _queue->tail->next = NULL;

  _queue->size = 0;
}

void insert_element(Queue *const _queue, int const _item) {
  _queue->tail->data = _item;

  Node *newNode = (Node *)malloc(sizeof(Node));
  _queue->tail->next = newNode;
  newNode->next = NULL;
  _queue->tail = newNode;

  ++_queue->size;
}

int remove_element(Queue *const _queue) {
  if (_queue->size == 0) {
    printf("Underflow Error!\n");
    return -1;
  }
  Node *toFree = _queue->head;
  int toReturn = toFree->next->data;
  _queue->head = toFree->next;
  free(toFree);
  --_queue->size;

  return toReturn;
}

void display(Queue const *const _queue) {
  printf("\n");
  if (_queue->size == 0) {
    printf("Queue is empty!\n");
    return;
  }
  printf("Queue Elements: ");
  for (Node *node  = _queue->head; node->next != _queue->tail; node = node->next) {
    printf("%d->", node->next->data);
  }
  printf("X\n");
}

int main() {
  Queue queue;
  initialize(&queue);

  int choice, value, poppedElement;
  do {
    printf("\nQueue Operations:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter value to be inserted: ");
      scanf("%d", &value);
      insert_element(&queue, value);
      display(&queue);
      break;
    case 2:
      poppedElement = remove_element(&queue);
      if (poppedElement != -1)
        printf("Deleted Element: %d\n", poppedElement);
      display(&queue);
      break;
    case 3:
      display(&queue);
      break;
    case 0:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 0);

  return 0;
}
