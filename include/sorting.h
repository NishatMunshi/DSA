#pragma once
#include <stdio.h>
#include <stdlib.h>

void swap(int *const _firstInteger, int *const _secondInteger)
{
  int temp = *_firstInteger;
  *_firstInteger = *_secondInteger;
  *_secondInteger = temp;
}
void displayArray(int const *const array, unsigned const length)
{
  printf("Array: {");

  for (unsigned index = 0; index < length; ++index)
    printf("%d%s", array[index], index < length - 1 ? ", " : "}\n");
}

void bubble_sort(int *const _array, unsigned const _length)
{
  unsigned numberOfComparisons = 0;

  int switched = 1;
  for (unsigned pass = 0; pass < _length - 1 && switched; ++pass)
  {
    for (unsigned bubbleIndex = 0; bubbleIndex < _length - 1 - pass; ++bubbleIndex)
    {
      switched = 0;
      numberOfComparisons++;
      if (_array[bubbleIndex] > _array[bubbleIndex + 1])
      {
        swap(_array + bubbleIndex, _array + bubbleIndex + 1);
        switched = 1;
      }
    }
  }
  printf("\nBubble sort done after %d comparisons\n", numberOfComparisons);
}

void quick_sort(int *const _array, int const _leftIndex, int const _rightIndex,
                unsigned *const _numberOfComparisons)
{
  if (_leftIndex > _rightIndex)
    return; // safety

  // partitioning
  int pivot = _array[_leftIndex], down = _leftIndex, up = _rightIndex;
  while (down < up)
  {
    (*_numberOfComparisons)++;
    while (_array[down] <= pivot && down < _rightIndex)
    {
      down++;
      (*_numberOfComparisons)++;
    }
    (*_numberOfComparisons)++;
    while (_array[up] > pivot && up > _leftIndex)
    {
      up--;
      (*_numberOfComparisons)++;
    }
    if (down < up)
      swap(_array + down, _array + up);
  }
  _array[_leftIndex] = _array[up];
  _array[up] = pivot;

  // recursion
  quick_sort(_array, _leftIndex, up - 1, _numberOfComparisons);
  quick_sort(_array, up + 1, _rightIndex, _numberOfComparisons);
}
void selection_sort(int *const _array, unsigned const _length)
{
  for (unsigned endOfRemainingElements = _length - 1; endOfRemainingElements > 0; --endOfRemainingElements)
  {
    // find largest of remaining elements
    unsigned largestElementIndex = 0;
    for (unsigned remainingElementIndex = 0; remainingElementIndex <= endOfRemainingElements; ++remainingElementIndex)
    {
      if (_array[remainingElementIndex] > _array[largestElementIndex])
      {
        largestElementIndex = remainingElementIndex;
      }
    }

    // swap it with last element
    swap(_array + endOfRemainingElements, _array + largestElementIndex);

    //debug
    displayArray(_array, _length);

  }
}

void insertion_sort(int *const _array, unsigned const _length)
{
  for (unsigned index = 1; index < _length; ++index)
  {
    int const toInsert = _array[index];

    // make room by moving all elements one place to the right until we hit an element smaller than toInsert
    int comparingIndex; // has to be int
    for (comparingIndex = index - 1; comparingIndex >= 0 && _array[comparingIndex] > toInsert; --comparingIndex)
    {
      _array[comparingIndex + 1] = _array[comparingIndex];
    }

    // insert toInsert in its proper place
    _array[comparingIndex + 1] = toInsert;

    // debug
    displayArray(_array, _length);
  }
}

void merge_sort(int *const _array, unsigned const _low, unsigned const _high)
{
  unsigned const length = _high + 1 - _low;
  if (length <= 1)
    return; // safety

  // recursion
  merge_sort(_array, _low, _low + length / 2 - 1);
  merge_sort(_array, _low + length / 2, _high);

  // merging
  int *const array1 = _array + _low, * array2 = _array + _low + length / 2;
  unsigned const length1 = length / 2,  length2 = _high + 1 - length / 2 - _low;
  unsigned array1Index = 0, array2Index = 0;
  int *const mergedArray = (int *)calloc(length1 + length2, sizeof(int));
  unsigned mergedArrayIndex = 0;

  // take in as many elements until one array is depleted
  while (array1Index < length1 && array2Index < length2)
  {
    if (array1[array1Index] < array2[array2Index])
      mergedArray[mergedArrayIndex++] = array1[array1Index++];
    else
      mergedArray[mergedArrayIndex++] = array2[array2Index++];
  }

  // take in the rest of the elements ( if there are any )
  while (array1Index < length1)
    mergedArray[mergedArrayIndex++] = array1[array1Index++];

  while (array2Index < length2)
    mergedArray[mergedArrayIndex++] = array2[array2Index++];

  // copy merged array over to array1
  for (unsigned index = 0; index < length1 + length2; ++index)
    array1[index] = mergedArray[index];

  free(mergedArray);
}