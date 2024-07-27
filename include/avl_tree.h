#ifndef DSA_AVL_TREE_H
#define DSA_AVL_TREE_H

typedef struct avl_tree_struct avl_tree;

avl_tree *avl_tree_create();
void      avl_tree_insert(avl_tree *tree, int data);
void      avl_tree_remove(avl_tree *tree, int data);
void      avl_tree_traverse_inorder(avl_tree *tree);
void      avl_tree_fill_array_inorder(avl_tree *tree, int *array);

#endif  // DSA_AVL_TREE_H
