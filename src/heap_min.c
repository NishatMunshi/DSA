#include "../include/heap_min.h"

#include <stdio.h>
#include <stdlib.h>

struct heap_min_struct {
    int *items;
    size_t size;
    size_t capacity;
};

heap_min *heap_min_create(size_t capacity) {
    heap_min *heap = malloc(sizeof(struct heap_min_struct));
    heap->items = malloc(capacity * sizeof(heap->items[0]));
    for (size_t i = 0; i < capacity; ++i) {
        heap->items[i] = __INT_MAX__;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

#define PARENT(child) ((child - 1) / 2)
#define MIN(a, b) (((heap->items[a]) < (heap->items[b])) ? (a) : (b))

static void heap_min_swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void heap_min_insert(heap_min *heap, int data) {
    if (heap->size >= heap->capacity) {
        printf("[HEAP_MIN ERROR]: heap overflow\n");
        return;
    }

    heap->items[heap->size++] = data;

    for (size_t child = heap->size - 1, parent = PARENT(child), min = MIN(parent, child);
         child > 0 && min != parent;
         child = parent, parent = PARENT(child), min = MIN(parent, child)) {
        heap_min_swap(heap->items + parent, heap->items + min);
    }
}

#define L_CHILD(parent) ((parent) * 2 + 1)
#define R_CHILD(parent) ((parent) * 2 + 2)
#define MIN3(a, b, c) (MIN((a), MIN((b), (c))))

int heap_min_remove(heap_min *heap) {
    if (heap->size == 0) {
        printf("[HEAP_MIN ERROR]: heap underflow\n");
        return -1;
    }

    int ret_value = heap->items[0];
    heap->items[0] = heap->items[--heap->size];

    for (size_t parent = 0, l_child = L_CHILD(parent), r_child = R_CHILD(parent), min = MIN3(parent, l_child, r_child);
         l_child < heap->size && min != parent;
         parent = min, l_child = L_CHILD(parent), r_child = R_CHILD(parent), min = MIN3(parent, l_child, r_child)) {
        heap_min_swap(heap->items + parent, heap->items + min);      
    }

    return ret_value;
}