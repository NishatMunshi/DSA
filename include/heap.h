#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Heap {
  int items[MAX_SIZE];
  unsigned size;
} Heap;

int maximum_heap(int const _a, int const _b) { return _a > _b ? _a : _b; }
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

void insert_element_heap(Heap *const _heap, int const _data,
                    unsigned *const _numberOfComparisons) {
  if (_heap->size == MAX_SIZE - 1) {
    printf("Heap is full\n");
    return;
  }

  _heap->items[_heap->size + 1] = _data;
  _heap->size++;

  *(_numberOfComparisons) += 1;
  for (unsigned currentIndex = _heap->size;
       currentIndex > 1 &&
       _heap->items[currentIndex] > _heap->items[parentIndex(currentIndex)];
       currentIndex = parentIndex(currentIndex)) {
    swap(_heap->items + currentIndex, _heap->items + parentIndex(currentIndex));
    *(_numberOfComparisons) += 1;
  }
}

void display(Heap *const _heap) {
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
int remove_element_heap(Heap *const _heap, unsigned *const _numberOFComparisons) {
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

    int maxItem = maximum_heap(thisItem, maximum_heap(leftChild, rightChild));

    *(_numberOFComparisons) +=1;
    if (leftChild == maxItem) {
      swap(_heap->items + currentIndex,
           _heap->items + leftChildIndex(currentIndex));
      currentIndex = leftChildIndex(currentIndex);
      continue;
    }
    *(_numberOFComparisons) +=1;
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
