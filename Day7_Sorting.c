#include "heap.h"
#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayArray(int *array, int length) {
  printf("\nArray:\n");
  for (unsigned i = 0; i < length; i++)
    printf("%d ", array[i]);
  printf("\n\n");
}

void heap_sort(int *const _array, unsigned const _length) {
  Heap *heap = create_heap();
  unsigned *numberOfComparisons = (unsigned *)malloc(sizeof(unsigned));
  *numberOfComparisons = 0;
  for (unsigned index = 0; index < _length; index++) {
    insert_element_heap(heap, _array[index], numberOfComparisons);
  }
  for (unsigned index = 0; index < _length; index++) {
    _array[_length - index - 1] =
        remove_element_heap(heap, numberOfComparisons);
  }
  printf("Heap sort done after %d comparisons\n", *numberOfComparisons);
}
void tree_sort(int *const _array, unsigned const _length) {
  Binary_Search_Tree *tree = create_tree();
  unsigned *numberOfComparisons = (unsigned *)malloc(sizeof(unsigned));
  *numberOfComparisons = 0;
  for (unsigned index = 0; index < _length; index++) {
    insert_element_tree(tree, _array[index], 0, numberOfComparisons);
  }
  printf("Tree sort done after %u comparisons\nSorted array: ",
         *numberOfComparisons);
  traverse_in_order(tree);
}

void merge(int arr[], int l, int m, int r,
           unsigned *const _numberOfComparisons) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    (*_numberOfComparisons) += 1;
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r, unsigned *const _numberOfComparisons) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m, _numberOfComparisons);
    mergeSort(arr, m + 1, r, _numberOfComparisons);

    merge(arr, l, m, r, _numberOfComparisons);
  }
}

int main() {
  printf("Enter array length: ");
  int length;
  scanf("%d", &length);
  int *array = (int *)malloc(length * sizeof(int));
  int *array2 = (int *)malloc(length * sizeof(int));
  int *array3 = (int *)malloc(length * sizeof(int));

  for (unsigned index = 0; index < length; index++) {
    printf("Enter array element %d: ", index);
    int data;
    scanf("%d", &data);
    array[index] = data;
    array2[index] = data;
    array3[index] = data;
  }
  displayArray(array, length);

  unsigned numberOfComparisons = 0;
  mergeSort(array, 0, length - 1, &numberOfComparisons);
  printf("Merge sort done after %d comparisons\n", numberOfComparisons);
  displayArray(array, length);

  heap_sort(array2, length);
  displayArray(array2, length);

  tree_sort(array3, length);x

  free(array);
  free(array2);
  free(array3);
  return 0;
}