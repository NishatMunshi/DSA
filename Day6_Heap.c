#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Heap {
  int items[MAX_SIZE];
  unsigned size;
} Heap;

int maximum(int const _a, int const _b) { return _a > _b ? _a : _b; }
void swap(int *const _a, int *const _b) {
  int temp = *_a;
  *_a = *_b;
  *_b = temp;
}

unsigned leftChildIndex(unsigned const _parentIndex) {
  return 2 * _parentIndex;
}
unsigned rightChildIndex(unsigned const _parentIndex) {
  return 2 * _parentIndex + 1;
}
unsigned parentIndex(unsigned const _childIndex) { return _childIndex >> 1; }

Heap *create_heap(void) {
  Heap *heap = (Heap *)malloc(sizeof(Heap));

  heap->size = 0;
  return heap;
}

void insert_element(Heap *const _heap, int const _data) {
  if (_heap->size == MAX_SIZE - 1) {
    printf("Heap is full\n");
    return;
  }

  _heap->items[_heap->size + 1] = _data;
  _heap->size++;

  for (unsigned currentIndex = _heap->size;
       currentIndex > 1 &&
       _heap->items[currentIndex] > _heap->items[parentIndex(currentIndex)];
       currentIndex = parentIndex(currentIndex))
    swap(_heap->items + currentIndex, _heap->items + parentIndex(currentIndex));
}

void display(Heap const *const _heap) {
  if (_heap->size == 0) {
    printf("Heap is empty\n");
    return;
  }
  unsigned depth = floor(log2(_heap->size));
  unsigned height = depth + 1;
  for (unsigned level = 0; level < height; ++level) {
    for (unsigned spaceIndex = 0; spaceIndex < pow(2, depth - level) - 1;
         ++spaceIndex)
      printf(" ");
    for (unsigned index = pow(2, level);
         index <= pow(2, level + 1) - 1 && index <= _heap->size; ++index) {
      printf("%d", _heap->items[index]);
      for (unsigned spaceIndex = 0; spaceIndex < pow(2, depth - level + 1) - 1;
           ++spaceIndex)
        printf(" ");
    }
    printf("\n");
  }
}
int remove_element(Heap *const _heap) {
  if (_heap->size == 0) {
    printf("Heap is empty\n");
    return -1;
  }
  int toReturn = _heap->items[1];

  _heap->items[1] = _heap->items[_heap->size];
  _heap->size--;

  unsigned currentIndex = 1;
  while (currentIndex <= _heap->size) {
    int thisItem = _heap->items[currentIndex];
    int leftChild, rightChild;

    if (leftChildIndex(currentIndex) > _heap->size)
      leftChild = INT_MIN;
    else
      leftChild = _heap->items[leftChildIndex(currentIndex)];

    if (rightChildIndex(currentIndex) > _heap->size)
      rightChild = INT_MIN;
    else
      rightChild = _heap->items[rightChildIndex(currentIndex)];

    int maxItem = maximum(thisItem, maximum(leftChild, rightChild));

    if (leftChild == maxItem) {
      swap(_heap->items + currentIndex,
           _heap->items + leftChildIndex(currentIndex));
      currentIndex = leftChildIndex(currentIndex);
      continue;
    }
    if (rightChild == maxItem) {
      swap(_heap->items + currentIndex,
           _heap->items + rightChildIndex(currentIndex));

      currentIndex = rightChildIndex(currentIndex);
      continue;
    }
    break;
  }
  return toReturn;
}

int main() {
  Heap *heap = create_heap();

  unsigned choice;
  int data, removedElement;
  do {
    printf("\nMenu:\n");
    printf("1. Insert Element\n");
    printf("2. Delete Element\n");
    printf("0. Exit\n\n");

    printf("Enter your choice: ");
    scanf("%u", &choice);
    printf("\n");

    switch (choice) {
    case 1:
      printf("Enter the data to be inserted: ");
      scanf("%d", &data);
      printf("\n");
      insert_element(heap, data);
      display(heap);
      break;
    case 2:
      removedElement = remove_element(heap);
      if (removedElement == -1)
        printf("Deletion Failed.\n");
      else
        printf("Removed Element = %d\n", removedElement);
      display(heap);
      break;
    case 0:
      printf("Exiting Program ...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
      break;
    }
  } while (choice != 0);
  return 0;
}