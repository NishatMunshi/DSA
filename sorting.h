#pragma once

#include <stdio.h>   // for printf
#include <stdlib.h>  // for size_t, calloc

// void sorting_fill_array_inorder(AVL_Tree const *const _tree, int *const _array) {
//     if (avltree_empty(_tree)) {
//         return;
//     }
//     static size_t nextFreeIndex = 0;
//     sorting_fill_array_inorder(_tree->root->leftChild, _array);
//     _array[nextFreeIndex++] = _tree->root->data;
//     sorting_fill_array_inorder(_tree->root->rightChild, _array);
// }

// void tree_sort(int *const _array, size_t const _length) {
//     AVL_Tree *const tree = avltree_create_tree();
//     for (size_t index = 0; index < _length; ++index) {
//         avltree_insert(tree, _array[index]);
//     }
//     sorting_fill_array_inorder(tree, _array);
// }

