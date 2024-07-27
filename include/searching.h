#ifndef DSA_SEARCHING_H
#define DSA_SEARCHING_H

#include <stddef.h>

size_t linear_search(int *array, size_t length, int num_to_search);

 // expects sorted array
size_t binary_search(int *array, size_t length, int num_to_search);

#endif // DSA_SEARCHING_H
