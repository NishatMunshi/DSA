#ifndef DSA_SORTING_H
#define DSA_SORTING_H

#include <stddef.h>

void bubble_sort(int *array, size_t length);
void selection_sort(int *array, size_t length);
void heap_sort(int *array, size_t length);
void insetion_sort(int *array, size_t length);
void quick_sort(int *array, size_t length);
void merge_sort(int *array, size_t length);
void tree_sort(int *array, size_t length);

#endif // DSA_SORTING_H