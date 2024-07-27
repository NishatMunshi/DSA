#include "../include/searching.h"

#include <stdio.h>

size_t linear_search(int *array, size_t length, int num_to_search) {
    for (size_t i = 0; i < length; ++i) {
        if (array[i] == num_to_search) {
            return i;
        }
    }
    printf("[LINEAR_SEARCH ERROR]: %i not found\n", num_to_search);
    return __SIZE_MAX__;
}

static size_t binary_search_recursive(int *array, size_t left, size_t right, int num_to_search) {
    size_t mid = (left + right) / 2;
    if (left > right) {
        printf("[BINARY_SEARCH ERROR]: %i not found\n", num_to_search);
        return __SIZE_MAX__;
    }
    if (array[mid] == num_to_search) {
        return mid;
    }
    if (num_to_search > array[mid]) {
        return binary_search_recursive(array, mid + 1, right, num_to_search);
    } else {
        return binary_search_recursive(array, left, mid - 1, num_to_search);
    }
}

size_t binary_search(int *array, size_t length, int num_to_search) {
    return binary_search_recursive(array, 0, length, num_to_search);
}
