#include <stdio.h>
#define QUEUESIZE 5

typedef struct Queue {
  int items[QUEUESIZE];
  unsigned front, rear, size;
} Queue;

void initialize(Queue *const _queue) {
  _queue->front = 0;
  _queue->rear = 0;
  _queue->size = 0;
}

void insert_element(Queue *const _queue, int const _item) {
  if (_queue->size == QUEUESIZE) {
    printf("\nOverflow Error!\n");
    return;
  }
  _queue->rear = _queue->rear % QUEUESIZE;
  _queue->items[_queue->rear++] = _item;
  _queue->size++;
}
int remove_element(Queue *const _queue) {
  if (_queue->size == 0) {
    printf("\nUnderflow Error!\n");
    return -1;
  }
  _queue->front = _queue->front % QUEUESIZE;
  _queue->size--;
  return _queue->items[_queue->front++];
}

void display(Queue const *const _queue) {
  printf("\nfront  = %d, rear = %d\n", _queue->front, _queue->rear);
  if (_queue->size == 0) {
    printf("Queue is empty!\n");
    return;
  }
  printf("Queue elements: ");
  for (int index = _queue->front, elements = 0; elements < _queue->size;
       index++, elements++) {
    if (index == QUEUESIZE)
      index = 0;
    printf("%d ", _queue->items[index]);
  }
  printf("\n");
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
