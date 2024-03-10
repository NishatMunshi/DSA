#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

void generateRandomIntegers(int *array, int length, int maxNum)
{
    unsigned char *is_used; /* flags */
    is_used = (unsigned char *)calloc(maxNum, sizeof(unsigned char));
    // unsigned char is_used[N] = { 0 };
    int i, r, in, im = 0;

    for (in = maxNum - length; in < maxNum && im < length; ++in)
    {
        r = rand() % (in + 1); /* generate a random number 'r' */
        if (is_used[r])        /* we already have 'r' */
            r = in;            /* use 'in' instead of the generated number */
        assert(!is_used[r]);
        array[im++] = r + 1; /* +1 since your range begins from 1 */
        is_used[r] = 1;
    }
}

void displayArray(int *array, int length)
{
    printf("\nArray:\n");
    for (unsigned i = 0; i < length; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void linear_search(int const *const _array, int const _length, int const _numberToSearch)
{
    unsigned numberOfComparisons = 0;
    for (unsigned index = 0; index < _length; ++index)
    {
        numberOfComparisons++;
        if (_array[index] == _numberToSearch)
        {
            printf("Linear search found %d at position %d after %d comparisons\n", _numberToSearch, index, numberOfComparisons);
            return;
        }
    }
    printf("Not found %d\n", _numberToSearch);
}

void bubble_sort(int *const _array, int const _length)
{
    for (int *i = _array; i < _array + _length; ++i)
    {
        for (int *j = _array; j < _array + _length; ++j)
        {
            if (*i < *j)
            {
                // swap
                int temp = *j;
                *j = *i;
                *i = temp;
            }
        }
    }
}
void binary_search(int const *const _array, int _length, int const _numberToSearch)
{
    unsigned leftMarker = 0, rightMarker = _length, numberOfComparisons = 0;
    unsigned midMarker = (leftMarker + rightMarker) / 2;
    while (1)
    {
        if (_length == 0)
        {
            printf("Not found %d\n", _numberToSearch);
            return;
        }
        numberOfComparisons++;
        if (_array[midMarker] == _numberToSearch)
        {
            printf("Binary Search found %d at position %d after %d comparisons\n", _numberToSearch, midMarker, numberOfComparisons);
            return;
        }
        numberOfComparisons++;
        if (_numberToSearch < _array[midMarker])
        {
            rightMarker = midMarker;
            midMarker = (leftMarker + rightMarker) / 2;
            _length /= 2;
            continue;
        }
        leftMarker = midMarker;
        midMarker = (leftMarker + rightMarker) / 2;
        _length /= 2;
    }
}

int main()
{
    printf("How many random numbers to be generated? ");
    int length;
    scanf("%d", &length);
    int maximumNumber;
    printf("Maximum value of random number (should be greater than %d)? ", length);
    scanf("%d", &maximumNumber);
    int *array = (int *)malloc(length * sizeof(int));

    generateRandomIntegers(array, length, maximumNumber);
    displayArray(array, length);

    printf("Enter number to search: ");
    int numberToSearch;
    scanf("%d", &numberToSearch);

    clock_t linearBegin = clock();
    linear_search(array, length, numberToSearch);
    clock_t linearEnd = clock();
    bubble_sort(array, length);
    displayArray(array, length);
    clock_t binaryBegin = clock();
    binary_search(array, length, numberToSearch);
    clock_t binaryEnd = clock();

    double linearTime = (double)(linearEnd- linearBegin);
    double binaryTime = (double)(binaryEnd- binaryBegin);
    printf("Time for Linear Search = %f miliseconds\n", linearTime);
    printf("Time for Binary Search = %f miliseconds\n", binaryTime);

    free(array);
    return 0;
}
