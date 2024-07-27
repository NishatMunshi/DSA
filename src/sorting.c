#include "../include/sorting.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/heap_min.h"

static void sorting_swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void bubble_sort(int *array, size_t length) {
    bool swapped = true;
    for (size_t i = 0; i < length && swapped; ++i) {
        swapped = false;
        for (size_t j = 0; j < length - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                sorting_swap(array + j, array + j + 1);
                swapped = true;
            }
        }
    }
}

void selection_sort(int *array, size_t length) {
    for (size_t i = length - 1; i > 0; --i) {
        size_t largest = 0;
        for (size_t j = 0; j <= i; ++j) {
            if (array[j] > array[largest]) {
                largest = j;
            }
        }
        sorting_swap(array + largest, array + i);
    }
}

void heap_sort(int *array, size_t length) {
    heap_min *heap = heap_min_create(length);
    for (size_t i = 0; i < length; ++i)
        heap_min_insert(heap, array[i]);
    for (size_t i = 0; i < length; ++i)
        array[i] = heap_min_remove(heap);
}

void insetion_sort(int *array, size_t length) {
    for (size_t i = length - 1; i > 0; --i) {
        int to_insert = array[i - 1];
        size_t j;
        for (j = i; j < length && array[j] < to_insert; ++j) {
            array[j - 1] = array[j];
        }
        array[j - 1] = to_insert;
    }
}

static size_t quick_sort_partition(int *array, size_t left, size_t right) {
    int pivot = array[left];
    size_t down = left, up = right;

    while (down < up) {
        while (array[down] <= pivot && down < right) {
            down++;
        }
        while (array[up] > pivot && up > left) {
            up--;
        }
        if (down < up) {
            sorting_swap(array + down, array + up);
        }
    }
    array[left] = array[up];
    array[up] = pivot;
    return up;
}

static void quick_sort_recursive(int *array, size_t left, size_t right) {
    // partitioning
    size_t pivot = quick_sort_partition(array, left, right);

    // recursion
    // only call quicksort on left subarray if it has at least two elements
    if (pivot > left + 1) {
        quick_sort_recursive(array, left, pivot - 1);
    }
    // only call quicksort on right subarray if it has at least two elements
    if (pivot < right - 1) {
        quick_sort_recursive(array, pivot + 1, right);
    }
}

void quick_sort(int *array, size_t length) {
    quick_sort_recursive(array, 0, length - 1);
}

void merge_sort_recursive(int *array, size_t low, size_t high) {
    size_t length = high + 1 - low;
    if (length <= 1) {
        return;
    }

    // recursion
    merge_sort_recursive(array, low, low + length / 2 - 1);
    merge_sort_recursive(array, low + length / 2, high);

    // merging
    int *array1 = array + low, *array2 = array + low + length / 2;
    size_t length1 = length / 2, length2 = high + 1 - length / 2 - low;
    size_t array1Index = 0, array2Index = 0;
    int *mergedArray = (int *)calloc(length1 + length2, sizeof(int));
    size_t mergedArrayIndex = 0;

    // take in as many elements as possible until one array is depleted
    while (array1Index < length1 && array2Index < length2) {
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

void merge_sort(int *array, size_t length) {
    merge_sort_recursive(array, 0, length - 1);
}