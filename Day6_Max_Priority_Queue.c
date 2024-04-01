#include "include/max_heap.h"

int main() {
  Heap *priorityQueue = create_heap();

  unsigned choice;
  int data, removedElement;
  do {
    printf("\nMenu:\n");
    printf("1. Insert Element\n");
    printf("2. Delete Element\n");
    printf("0. Exit\n");

    printf("Enter your choice: ");
    scanf("%u", &choice);
    // printf("\n");

    switch (choice) {
    case 1:
      printf("Enter the data to be inserted: ");
      scanf("%d", &data);
      // printf("\n");
      insert_element(priorityQueue, data);
      break;
    case 2:
      removedElement = remove_element(priorityQueue);
      if (removedElement == -1)
        printf("Deletion Failed.\n");
      else
        printf("Removed Element = %d\n", removedElement);
      break;
    case 0:
      printf("Exiting Program ...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
      break;
    }
    if(priorityQueue->size > 0)
      printf("Front Element = %d\n", priorityQueue->items[1]);
  } while (choice != 0);
  return 0;
}