#include "../include/sorting.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/avl_tree.h"
#include "../include/heap.h"

static void sorting_swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void bubble_sort(int* array, size_t length) {
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

void selection_sort(int* array, size_t length) {
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
static int compare(int x, int y) { return  y - x; }
void heap_sort(int* array, size_t length) {
    heap* heap = heap_create(length, compare);
    for (size_t i = 0; i < length; ++i)
        heap_insert(heap, array[i]);
    for (size_t i = 0; i < length; ++i)
        array[i] = heap_remove(heap);
}

void insetion_sort(int* array, size_t length) {
    for (size_t i = length - 1; i > 0; --i) {
        int to_insert = array[i - 1];
        size_t j;
        for (j = i; j < length && array[j] < to_insert; ++j) {
            array[j - 1] = array[j];
        }
        array[j - 1] = to_insert;
    }
}

static size_t quick_sort_partition(int* array, size_t left, size_t right) {
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

static void quick_sort_recursive(int* array, size_t left, size_t right) {
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

void quick_sort(int* array, size_t length) {
    quick_sort_recursive(array, 0, length - 1);
}

static void __attribute_maybe_unused__ merge_no_extra_space(int* array1, int* array2, size_t len1, size_t len2) {
    for (size_t i = 0; i < len1; ++i) {
        if (array1[i] > array2[0]) {
            sorting_swap(array1 + i, array2 + 0);
            for (size_t j = 0; j < len2 - 1 && array2[j] > array2[j + 1]; ++j) {
                sorting_swap(array2 + j, array2 + j + 1);
            }
        }
    }
}

static void merge(int* array1, int* array2, size_t len1, size_t len2) {
    int* merged_array = calloc(len1 + len2, sizeof(array1[0]));
    size_t array1_index = 0, array2_index = 0;
    size_t merged_array_index = 0;

    // take in as many elements as possible until one array is depleted
    while (array1_index < len1 && array2_index < len2) {
        if (array1[array1_index] < array2[array2_index])
            merged_array[merged_array_index++] = array1[array1_index++];
        else
            merged_array[merged_array_index++] = array2[array2_index++];
    }

    // take in the rest of the elements ( if there are any )
    while (array1_index < len1)
        merged_array[merged_array_index++] = array1[array1_index++];

    while (array2_index < len2)
        merged_array[merged_array_index++] = array2[array2_index++];

    // copy merged array over to array1
    for (size_t index = 0; index < len1 + len2; ++index)
        array1[index] = merged_array[index];

    free(merged_array);
}

static void merge_sort_recursive(int* array, size_t low, size_t high) {
    size_t length = high + 1 - low;
    if (length <= 1) {
        return;
    }

    // recursion
    merge_sort_recursive(array, low, low + length / 2 - 1);
    merge_sort_recursive(array, low + length / 2, high);

    // merging
    int* array1 = array + low, * array2 = array + low + length / 2;
    size_t len1 = length / 2, len2 = high + 1 - length / 2 - low;
    merge(array1, array2, len1, len2);
}

void merge_sort(int* array, size_t length) {
    merge_sort_recursive(array, 0, length - 1);
}

void tree_sort(int* array, size_t length) {
    avl_tree* tree = avl_tree_create();
    for (size_t i = 0; i < length; ++i) {
        avl_tree_insert(tree, array[i]);
    }
    avl_tree_fill_array_inorder(tree, array);
}
