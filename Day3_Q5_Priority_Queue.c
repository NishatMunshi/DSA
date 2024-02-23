#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Queue {
  Node *front, *rear;
  size_t size;
} Queue;

void initialize(Queue *const _queue) {
  _queue->front = (Node *)malloc(sizeof(Node));
  _queue->rear = (Node *)malloc(sizeof(Node));
  _queue->front->next = _queue->rear;
  _queue->rear->next = NULL;

  _queue->front->data = INT_MIN; // very important line
  _queue->rear->data = INT_MAX;  // very important line

  _queue->size = 0;
}
void display(Queue const *const _queue) {
  printf("Queue elements: ");
  for (Node *node = _queue->front->next; node != _queue->rear;
       node = node->next) {
    printf("%d ", node->data);
  }
  printf("\n");
}

void insert_element(Queue *const _queue, int const _data) {
  // search the queue for this or higher data
  Node *prevNode = _queue->front;
  for (; prevNode != _queue->rear; prevNode = prevNode->next) {
    if (prevNode->next->data >= _data) {
      break;
    }
  }
  Node *nextNode = prevNode->next;

  // insert the element in between the Nodes
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = _data;
  prevNode->next = newNode;
  newNode->next = nextNode;

  ++_queue->size;
}
int remove_element(Queue *const _queue) {
  if (_queue->size == 0) {
    printf("Underflow Error!\n");
    return -1;
  }
  Node *toFree = _queue->front;
  int toReturn = toFree->next->data;
  _queue->front = toFree->next;
  free(toFree);
  --_queue->size;

  return toReturn;
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
