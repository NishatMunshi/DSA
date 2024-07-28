#ifndef DSA_HEAP_H
#define DSA_HEAP_H

#include <stddef.h>

typedef struct heap_struct heap;

heap *heap_create(size_t capacity, int (*compare)(int x, int y));
void  heap_insert(heap *heap, int data);
int   heap_remove(heap *heap);

#endif // DSA_HEAP_H