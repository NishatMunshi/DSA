#include "../include/main.h"

#include <stdio.h>

#include "../include/sorting.h"

#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))
int main() {
    int array[] = {3, 6, 7, 5 , 4, 9,  1};
    merge_sort(array, ARRAY_LEN(array));
    for(size_t i = 0; i < ARRAY_LEN(array); ++i) {
        printf("%i ", array[i]);
    } printf("\n");
    return 0;
}