#ifndef DSA_HEAP_MIN_H
#define DSA_HEAP_MIN_H

#include <stddef.h>

typedef struct heap_min_struct heap_min;

heap_min *heap_min_create(size_t capacity);
void      heap_min_insert(heap_min *heap, int data);
int       heap_min_remove(heap_min *heap);

#endif // DSA_HEAP_MIN_H