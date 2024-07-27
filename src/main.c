#include "../include/main.h"
#include "../include/list.h"
#include "../include/sorting.h"

#include <stdio.h>

#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

int main() {
    int array[] = { 3, 6, 7, 5, 4, 9, 1 };
    tree_sort(array, ARRAY_LEN(array));

    list* list = list_create();
    for (size_t i = 0; i < ARRAY_LEN(array); ++i) {
        list_add_before(list, 0, array[i]);
    }

    return 0;
}