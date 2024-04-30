#include "include/sorting.h"
#include "include/searching.h"

int main()
{
    int array[] = {50, 12, 65, 62, 100, 5, 1, 63, 123, 45, 78, 90, 34, 23, 11, 76, 89, 2, 4, 6, 8, 10, 14, 16, 18};

    unsigned const length = 25;
    merge_sort(array, 0, length -1);
    displayArray(array, length);

    int const numberToSearch = 90;
    int returnValue = binary_search(array, 0, length -1, numberToSearch);
    printf("Found %d at index %d\n", numberToSearch, returnValue);

    return 0;
}