#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/sorting.h"

void generateRandomIntegers(int *array, int length, int maxNum) {
  unsigned char *is_used; /* flags */
  is_used = (unsigned char *)calloc(maxNum, sizeof(unsigned char));
  // unsigned char is_used[N] = { 0 };
  int i, r, in, im = 0;

  for (in = maxNum - length; in < maxNum && im < length; ++in) {
    r = rand() % (in + 1); /* generate a random number 'r' */
    if (is_used[r])        /* we already have 'r' */
      r = in;              /* use 'in' instead of the generated number */
    assert(!is_used[r]);
    array[im++] = r + 1; /* +1 since your range begins from 1 */
    is_used[r] = 1;
  }
}
void linear_search(int const *const _array, int const _length,
                   int const _numberToSearch) {
  unsigned numberOfComparisons = 0;
  for (unsigned index = 0; index < _length; ++index) {
    numberOfComparisons++;
    if (_array[index] == _numberToSearch) {
      printf("Linear search found %d at position %d after %d comparisons\n",
             _numberToSearch, index, numberOfComparisons);
      return;
    }
  }
  printf("Linear Search did not find %d\n", _numberToSearch);
}

void binary_search(int *const _array, int _length, int const _numberToSearch) {

  unsigned leftMarker = 0, rightMarker = _length, numberOfComparisons = 0;
  unsigned midMarker = (leftMarker + rightMarker) / 2;
  while (1) {
    if (_length == 0) {
      printf("Binary Search did not find %d\n", _numberToSearch);
      return;
    }
    numberOfComparisons++;
    if (_array[midMarker] == _numberToSearch) {
      printf("Binary Search found %d at position %d after %d comparisons\n",
             _numberToSearch, midMarker, numberOfComparisons);
      return;
    }
    numberOfComparisons++;
    if (_numberToSearch < _array[midMarker]) {
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

int main() {
  printf("How many random numbers to be generated? ");
  int length;
  scanf("%d", &length);
  int maximumNumber;
  printf("Maximum value of random number (should be greater than %d)? ",
         length);
  scanf("%d", &maximumNumber);
  int *array = (int *)malloc(length * sizeof(int));

  generateRandomIntegers(array, length, maximumNumber);
  displayArray(array, length);

  int numberToSearch;
  printf("Enter number to search: ");
  scanf("%d", &numberToSearch);

  linear_search(array, length, numberToSearch);

  bubble_sort(array, length); // binary search requires sorted array
  printf("Sorted ");
  displayArray(array, length);
  binary_search(array, length, numberToSearch);

  printf("\nEnter number to search: ");
  scanf("%d", &numberToSearch);

  linear_search(array, length, numberToSearch);
  binary_search(array, length, numberToSearch);

  free(array);
  return 0;
}
