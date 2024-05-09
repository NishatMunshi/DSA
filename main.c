#include "include/max_heap.h"

#include <stdio.h>

int main()
{
    Max_Heap *heap = maxheap_create_heap(100);

    for (unsigned n = 0; n < 10; ++n)
    {
        maxheap_insert(heap, n);
    }

    for (unsigned n = 0; n < 7; ++n)
    {
        printf("\n");
        maxheap_remove(heap);
        maxheap_display(heap);
    }
    printf("\n");

    return 0;
}