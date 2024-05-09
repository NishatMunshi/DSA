#pragma once

#include <stdlib.h> // for malloc
#include <assert.h> // for assert
#include <math.h>   // for floor, log and pow
#include <stdio.h>  // for printf

typedef struct Max_Heap
{
  int *items;
  size_t size;
  size_t capacity;
} Max_Heap;

Max_Heap *maxheap_create_heap(size_t const _maxSize)
{
  Max_Heap *heap = (Max_Heap *)malloc(sizeof(Max_Heap));

  heap->items = (int *)malloc(_maxSize * sizeof(int));
  heap->capacity = _maxSize - 1; // 1 based indexing
  heap->size = 0;

  // preparing the heap this way so that we dont have to do a lot of checks afterwards
  heap->items[0] = INT_MAX;
  for (size_t index = 1; index < _maxSize; ++index)
  {
    heap->items[index] = INT_MIN;
  }

  return heap;
}
void maxheap_swap(int *const _int1, int *const _int2)
{
  int const temp = *_int1;
  *_int1 = *_int2;
  *_int2 = temp;
}

void maxheap_insert(Max_Heap *const _heap, int const _data)
{
  assert(_heap->size < _heap->capacity);

  // insert new item
  _heap->items[_heap->size + 1] = _data;
  ++_heap->size;

  // fix heap structure
  for (size_t currentIndex = _heap->size; currentIndex > 1;)
  {
    size_t const parentIndex = currentIndex / 2;

    int const largest = __max(_heap->items[parentIndex], _heap->items[currentIndex]);
    if (largest == _heap->items[parentIndex])
    {
      return;
    }
    else
    {
      maxheap_swap(_heap->items + parentIndex, _heap->items + currentIndex);
      currentIndex = parentIndex;
      continue;
    }
  }
}
int maxheap_remove(Max_Heap *const _heap)
{
  assert(_heap->size > 0);

  // extract the item to delete
  int const toReturn = _heap->items[1];
  _heap->items[1] = _heap->items[_heap->size];
  _heap->items[_heap->size] = INT_MIN; // this line reduces a lot of edge case checking
  --_heap->size;

  // fix heap structure
  for (size_t currentIndex = 1, leftChildIndex = 2 * currentIndex, rightChildIndex = 2 * currentIndex + 1;
       leftChildIndex <= _heap->capacity && rightChildIndex <= _heap->capacity; /*avoiding seg fault*/
       leftChildIndex = 2 * currentIndex, rightChildIndex = 2 * currentIndex + 1)
  {
    int const largest = __max(_heap->items[currentIndex],
                              __max(_heap->items[leftChildIndex], _heap->items[rightChildIndex]));

    if (largest == _heap->items[currentIndex])
    {
      return toReturn;
    }
    else if (largest == _heap->items[leftChildIndex])
    {
      maxheap_swap(_heap->items + currentIndex, _heap->items + leftChildIndex);
      currentIndex = leftChildIndex;
      continue;
    }
    else
    {
      maxheap_swap(_heap->items + currentIndex, _heap->items + rightChildIndex);
      currentIndex = rightChildIndex;
      continue;
    }
  }
  return toReturn;
}
void maxheap_display(Max_Heap const *const _heap)
{
  unsigned const depth = floor(log2(_heap->size));
  unsigned const height = depth + 1;

  for (unsigned level = 0; level < height; ++level)
  {
    for (unsigned spaceIndex = 0; spaceIndex < pow(2, depth - level) - 1; ++spaceIndex)
    {
      printf(" ");
    }
    for (unsigned index = pow(2, level); index <= pow(2, level + 1) - 1 && index <= _heap->size; ++index)
    {
      printf("%d", _heap->items[index]);
      for (unsigned spaceIndex = 0; spaceIndex < pow(2, depth - level + 1) - 1; ++spaceIndex)
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}