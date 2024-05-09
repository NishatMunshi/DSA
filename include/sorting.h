#pragma once

#include <stdio.h>	  // for printf
#include <stdlib.h>	  // for size_t, calloc
#include "avl_tree.h" // for treesort
#include "max_heap.h" // for heapsort

void sorting_swap(int *const _firstInteger, int *const _secondInteger)
{
	int const temp = *_firstInteger;
	*_firstInteger = *_secondInteger;
	*_secondInteger = temp;
}
void display_array(int const *const array, size_t const length)
{
	printf("Array: {");

	for (size_t index = 0; index < length; ++index)
		printf("%d%s", array[index], index < length - 1 ? ", " : "}\n");
}
void sorting_fill_array_inorder(AVL_Tree const *const _tree, int *const _array)
{
	if (avltree_empty(_tree))
	{
		return;
	}
	static size_t nextFreeIndex = 0;
	sorting_fill_array_inorder(_tree->root->leftChild, _array);
	_array[nextFreeIndex++] = _tree->root->data;
	sorting_fill_array_inorder(_tree->root->rightChild, _array);
}

void bubble_sort(int *const _array, size_t const _length)
{
	int switchedInLastPass = 1;
	for (size_t pass = 0; pass < _length - 1 && switchedInLastPass; ++pass)
	{
		switchedInLastPass = 0;
		for (size_t bubbleIndex = 0; bubbleIndex < _length - 1 - pass; ++bubbleIndex)
		{
			if (_array[bubbleIndex] > _array[bubbleIndex + 1])
			{
				sorting_swap(_array + bubbleIndex, _array + bubbleIndex + 1);
				// display_array(_array, _length);
				switchedInLastPass = 1;
			}
		}
	}
}
void quick_sort(int *const _array, size_t const _leftIndex, size_t const _rightIndex)
{
	// partitioning
	int pivot = _array[_leftIndex];
	size_t down = _leftIndex, up = _rightIndex;

	while (down < up)
	{
		while (_array[down] <= pivot && down < _rightIndex)
		{
			down++;
		}
		while (_array[up] > pivot && up > _leftIndex)
		{
			up--;
		}
		if (down < up)
		{
			sorting_swap(_array + down, _array + up);
		}
	}
	_array[_leftIndex] = _array[up];
	_array[up] = pivot;

	// recursion
	// only call quicksort on left subarray if it has at least two elements
	if (up > _leftIndex + 1)
	{
		quick_sort(_array, _leftIndex, up - 1);
	}
	// only call quicksort on right subarray if it has at least two elements
	if (up < _rightIndex - 1)
	{
		quick_sort(_array, up + 1, _rightIndex);
	}
}

void selection_sort(int *const _array, size_t const _length)
{
	for (size_t endOfRemainingElements = _length - 1; endOfRemainingElements > 0; --endOfRemainingElements)
	{
		// find largest of remaining elements
		size_t largestElementIndex = 0;
		for (size_t remainingElementIndex = 0; remainingElementIndex <= endOfRemainingElements; ++remainingElementIndex)
		{
			if (_array[remainingElementIndex] > _array[largestElementIndex])
			{
				largestElementIndex = remainingElementIndex;
			}
		}

		// swap it with last element
		sorting_swap(_array + largestElementIndex, _array + endOfRemainingElements);

		// debug
		// display_array(_array, _length);
	}
}
void tree_sort(int *const _array, size_t const _length)
{
	AVL_Tree *const tree = avltree_create_tree();
	for (size_t index = 0; index < _length; ++index)
	{
		avltree_insert(tree, _array[index]);
	}
	sorting_fill_array_inorder(tree, _array);
}
void heap_sort(int *const _array, size_t const _length)
{
	Max_Heap *heap = maxheap_create_heap(_length + 1);

	for (size_t index = 0; index < _length; ++index)
	{
		maxheap_insert(heap, _array[index]);
	}
	for (size_t index = 0; index < _length; ++index)
	{
		_array[_length - 1 - index] = maxheap_remove(heap);
		// maxheap_display(heap);
	}
}

void insertion_sort(int *const _array, size_t const _length)
{
	// to begin, _array[_length-1] is a sorted file of length 1
	// each time through outer loop size of sorted file increases
	for (size_t startOfSortedFile = _length - 1; startOfSortedFile > 0; --startOfSortedFile)
	{
		// pick an element just outside of the sorted file to insert into the sorted file
		int const toInsert = _array[startOfSortedFile - 1];

		// traverse through the sorted file and
		// make room by moving all elements one place to the left until we hit an element bigger than toInsert
		size_t sortedFileIndex;
		for (sortedFileIndex = startOfSortedFile; sortedFileIndex < _length && _array[sortedFileIndex] < toInsert; ++sortedFileIndex)
		{
			_array[sortedFileIndex - 1] = _array[sortedFileIndex];
			// display_array(_array, _length);
		}

		// insert toInsert in its proper place
		_array[sortedFileIndex - 1] = toInsert;

		// debug
		// display_array(_array, _length);
	}
}

void merge_sort(int *const _array, size_t const _low, size_t const _high)
{
	size_t const length = _high + 1 - _low;
	if (length <= 1)
	{
		// no need to sort an array of length 1 or less
		return;
	}
	// recursion
	merge_sort(_array, _low, _low + length / 2 - 1);
	merge_sort(_array, _low + length / 2, _high);

	// merging
	int *const array1 = _array + _low, *array2 = _array + _low + length / 2;
	size_t const length1 = length / 2, length2 = _high + 1 - length / 2 - _low;
	size_t array1Index = 0, array2Index = 0;
	int *const mergedArray = (int *)calloc(length1 + length2, sizeof(int));
	size_t mergedArrayIndex = 0;

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
	for (size_t index = 0; index < length1 + length2; ++index)
		array1[index] = mergedArray[index];

	free(mergedArray);
}