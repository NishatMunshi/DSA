#include "../include/main.h"
#include "../include/heap.h"
#include <stdio.h>

int compare(int x, int y)
{
    return y - x;
}
int main() {
    heap* heap = heap_create(10, compare);
    heap_insert(heap, 1);
    heap_insert(heap, 3);
    heap_insert(heap, 2);
    heap_insert(heap, 5);
    heap_insert(heap, 6);
    heap_insert(heap, 4);


    printf("%i ", heap_remove(heap));
    printf("%i ", heap_remove(heap));
    printf("%i ", heap_remove(heap));
    printf("%i ", heap_remove(heap));
    printf("%i ", heap_remove(heap));
    printf("%i ", heap_remove(heap));
    return 0;
}