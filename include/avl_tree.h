#pragma once

#include <stdlib.h> // for maclloc
#include <assert.h> // for assert
#include <stdio.h>  // for printf

struct AVL_Tree;
typedef struct AVL_Tree_Node
{
  int data;
  struct AVL_Tree *leftChild, *rightChild;
} AVL_Tree_Node;

// wrapper around root node
typedef struct AVL_Tree
{
  AVL_Tree_Node *root;
  size_t size;
  size_t height;
} AVL_Tree;

// checks if a tree is empty (ie its root is NULL)
int avltree_empty(AVL_Tree const *const _tree) { return _tree->root == NULL; }
// checks if a non empty tree is a leaf or not
int avltree_leaf(AVL_Tree const *const _tree)
{
  return !(avltree_empty(_tree)) && avltree_empty(_tree->root->leftChild) && avltree_empty(_tree->root->rightChild);
}
int avltree_has_left_child(AVL_Tree const *const _tree)
{
  return !(avltree_empty(_tree)) && !avltree_empty(_tree->root->leftChild);
}
int avltree_has_right_child(AVL_Tree const *const _tree)
{
  return !(avltree_empty(_tree)) && !avltree_empty(_tree->root->rightChild);
}
long avltree_balance_factor(AVL_Tree const *const _tree)
{
  if (avltree_empty(_tree))
  {
    return 0;
  }
  return _tree->root->leftChild->height - _tree->root->rightChild->height;
}
int avltree_balanced(AVL_Tree const *const _tree)
{
  return abs(avltree_balance_factor(_tree)) < 2;
}
void avltree_update_size(AVL_Tree *const _tree)
{
  if (avltree_empty(_tree))
  {
    _tree->size = 0;
    return;
  }

  _tree->size = 1 + _tree->root->leftChild->size + _tree->root->rightChild->size;
}
void avltree_update_height(AVL_Tree *const _tree)
{
  if (avltree_empty(_tree))
  {
    _tree->size = 0;
    return;
  }
  _tree->height = 1 + __max(_tree->root->leftChild->height, _tree->root->rightChild->height);
}
void avltree_ll_rotate(AVL_Tree *const _tree)
{
  // make copies of some information (only copying some integers and pointers, not a big deal)
  AVL_Tree const rightChildOfleftChild = *(_tree->root->leftChild->root->rightChild);
  AVL_Tree const rightChild = *(_tree->root->rightChild);
  AVL_Tree const leftChild = *(_tree->root->leftChild);
  AVL_Tree const _treeTree = *(_tree);

  // now we can copy informations to correct places
  *(_tree) = leftChild;
  *(_tree->root->rightChild) = _treeTree;
  *(_tree->root->rightChild->root->rightChild) = rightChild;
  *(_tree->root->rightChild->root->leftChild) = rightChildOfleftChild;

  avltree_update_size(_tree->root->rightChild);
  avltree_update_height(_tree->root->rightChild);
  avltree_update_size(_tree);
  avltree_update_height(_tree);
}
void avltree_rr_rotate(AVL_Tree *const _tree)
{
  // make copies of some information (only copying some integers and pointers, not a big deal)
  AVL_Tree const leftChildOfrightChild = *(_tree->root->rightChild->root->leftChild);
  AVL_Tree const leftChild = *(_tree->root->leftChild);
  AVL_Tree const rightChild = *(_tree->root->rightChild);
  AVL_Tree const thisTree = *(_tree);

  // now we can copy informations to correct places
  *(_tree) = rightChild;
  *(_tree->root->leftChild) = thisTree;
  *(_tree->root->leftChild->root->leftChild) = leftChild;
  *(_tree->root->leftChild->root->rightChild) = leftChildOfrightChild;

  avltree_update_size(_tree->root->leftChild);
  avltree_update_height(_tree->root->leftChild);
  avltree_update_size(_tree);
  avltree_update_height(_tree);
}
void avltree_lr_rotate(AVL_Tree *const _tree)
{
  avltree_rr_rotate(_tree->root->leftChild);
  avltree_ll_rotate(_tree);
}
void avltree_rl_rotate(AVL_Tree *const _tree)
{
  avltree_ll_rotate(_tree->root->rightChild);
  avltree_rr_rotate(_tree);
}

// allocates memory for an avltree_empty tree
AVL_Tree *avltree_create_tree(void)
{
  AVL_Tree *tree = (AVL_Tree *)malloc(sizeof(AVL_Tree));
  tree->root = NULL;
  tree->height = 0;
  tree->size = 0;

  return tree;
}
// allocates memory for a new node with two empty subtrees
AVL_Tree_Node *avltree_create_node(int const _data)
{
  AVL_Tree_Node *node = (AVL_Tree_Node *)malloc(sizeof(AVL_Tree_Node));
  node->data = _data;
  node->leftChild = avltree_create_tree();
  node->rightChild = avltree_create_tree();

  return node;
}
void avltree_insert(AVL_Tree *const _tree, int const _data)
{
  if (avltree_empty(_tree))
  {
    _tree->root = avltree_create_node(_data);
  }
  else if (_data < _tree->root->data)
  {
    avltree_insert(_tree->root->leftChild, _data);

    // necessary rotations LL or LR
    if (!avltree_balanced(_tree))
    {
      if (_data < _tree->root->leftChild->root->data)
      {
        avltree_ll_rotate(_tree);
      }
      else
      {
        avltree_lr_rotate(_tree);
      }
    }
  }
  else
  {
    avltree_insert(_tree->root->rightChild, _data);

    // necessary rotations RR or RL
    if (!avltree_balanced(_tree))
    {
      if (_data < _tree->root->rightChild->root->data)
      {
        avltree_rl_rotate(_tree);
      }
      else
      {
        avltree_rr_rotate(_tree);
      }
    }
  }

  avltree_update_size(_tree);
  avltree_update_height(_tree);
}
void avltree_remove(AVL_Tree *const _tree, int const _data)
{
  assert(!avltree_empty(_tree));

  if (_tree->root->data == _data)
  {
    if (avltree_leaf(_tree))
    {
      free(_tree->root->leftChild);
      free(_tree->root->rightChild);
      free(_tree->root);
      _tree->root = NULL;
    }
    else if (avltree_has_left_child(_tree) && !avltree_has_right_child(_tree))
    {
      AVL_Tree const leftChild = *(_tree->root->leftChild);
      free(_tree->root->leftChild);
      free(_tree->root->rightChild);
      free(_tree->root);
      _tree->root = NULL;

      *_tree = leftChild;
    }
    else if (avltree_has_right_child(_tree) && !avltree_has_left_child(_tree))
    {
      AVL_Tree const rightChild = *(_tree->root->rightChild);
      free(_tree->root->leftChild);
      free(_tree->root->rightChild);
      free(_tree->root);
      _tree->root = NULL;

      *_tree = rightChild;
    }
    else
    {
      // find inorder successor
      AVL_Tree *inOrderSuccessor = _tree->root->rightChild;
      while (!avltree_empty(inOrderSuccessor->root->leftChild))
      {
        inOrderSuccessor = inOrderSuccessor->root->leftChild;
      }

      _tree->root->data = inOrderSuccessor->root->data;
      avltree_remove(_tree->root->rightChild, _tree->root->data);
    }
  }
  else if (_data < _tree->root->data)
  {
    avltree_remove(_tree->root->leftChild, _data);
    if (!avltree_balanced(_tree))
    {
      if (avltree_balance_factor(_tree->root->rightChild) <= 0)
      {
        avltree_rr_rotate(_tree);
      }
      else
      {
        avltree_rl_rotate(_tree);
      }
    }
  }
  else
  {
    avltree_remove(_tree->root->rightChild, _data);
    if (avltree_balanced(_tree))
    {
      if (avltree_balance_factor(_tree->root->leftChild) >= 0)
      {
        avltree_ll_rotate(_tree);
      }
      else
      {
        avltree_lr_rotate(_tree);
      }
    }
  }
  avltree_update_size(_tree);
  avltree_update_height(_tree);
}
void avltree_traverse_in_order(AVL_Tree const *const _tree)
{
  if (avltree_empty(_tree))
    return;

  avltree_traverse_in_order(_tree->root->leftChild);
  printf("%d ", _tree->root->data);
  avltree_traverse_in_order(_tree->root->rightChild);
}