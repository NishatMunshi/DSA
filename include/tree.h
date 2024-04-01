#include <stdio.h>
#include <stdlib.h>

struct Binary_Search_Tree;
typedef struct Node {
  int data;
  struct Binary_Search_Tree *leftChild, *rightChild;
} Node;

// wrapper around root node
typedef struct Binary_Search_Tree {
  Node *root;
} Binary_Search_Tree;

// checks if a tree is empty (ie its root is NULL)
int empty(Binary_Search_Tree const *const _tree) { return _tree->root == NULL; }
// checks if a on empty tree is a leaf or not
int leaf(Binary_Search_Tree const *const _tree) {
  if (empty(_tree))
    return 0;
  return empty(_tree->root->leftChild) && empty(_tree->root->rightChild);
}

// allocates memory for an empty tree
Binary_Search_Tree *create_tree(void) {
  Binary_Search_Tree *tree =
      (Binary_Search_Tree *)malloc(sizeof(Binary_Search_Tree));
  tree->root = NULL;

  return tree;
}

// leaves the argument as an empty tree
void delete_tree(Binary_Search_Tree *const _tree) {
  if (empty(_tree))
    return;

  delete_tree(_tree->root->leftChild);  // first make the left child empty
  delete_tree(_tree->root->rightChild); // then make the right child empty

  // now that children are empty we can free its children and its root and mark
  // it as empty
  free(_tree->root->leftChild);
  free(_tree->root->rightChild);
  free(_tree->root);
  _tree->root = NULL; // mark this tree as empty
}

// allocates memory for a new node with a brand new id and two empty subtrees
Node *create_node(int const _data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = _data;
  newNode->leftChild = create_tree();
  newNode->rightChild = create_tree();

  return newNode;
}

unsigned maximum_tree(unsigned const _a, unsigned const _b) {
  return _a > _b ? _a : _b;
}
unsigned number_of_levels(Binary_Search_Tree const *const _tree) {
  if (empty(_tree))
    return 0;
  if (leaf(_tree))
    return 1;
  return 1 + maximum_tree(number_of_levels(_tree->root->leftChild),
                     number_of_levels(_tree->root->rightChild));
}

int insert_element_tree(Binary_Search_Tree *const _tree, int const _data,
                   unsigned const _level, unsigned *const _numberOfComparisons) {
  // try to insert in this level
  if (empty(_tree)) {
    _tree->root = create_node(_data);
    // printf("Insertion done at level %d\n", _level);
    return 1;
  }

  // try to insert in left child
  int insertedInLeftChild = 0;
  *(_numberOfComparisons) += 1;
  if (_data < _tree->root->data)
    insertedInLeftChild =
        insert_element_tree(_tree->root->leftChild, _data, _level + 1, _numberOfComparisons);
  if (insertedInLeftChild)
    return 1;

  // if failed, try to insert in right child
  return insert_element_tree(_tree->root->rightChild, _data, _level + 1, _numberOfComparisons);
}

int remove_element_tree(Binary_Search_Tree *const _tree, int const _data,
                   unsigned const _level) {
  if (empty(_tree))
    return 0;
  if (_data == _tree->root->data) {
    if (leaf(_tree)) {
      // free its empty subtree wrappers
      free(_tree->root->leftChild);
      free(_tree->root->rightChild);

      printf("Deleting Node data %d at level %d\n", _tree->root->data, _level);
      // make this tree empty
      delete_tree(_tree);
      return 1;
    }
    if (empty(_tree->root->leftChild)) {
      // free the left child tree wrapper
      free(_tree->root->leftChild);
      // save right child's root address in a variable
      Node *rightChildRoot = _tree->root->rightChild->root;
      // free right child tree wrapper
      free(_tree->root->rightChild);
      // free this tree's root node (actual deletion)
      printf("Deleting Node data %d at level %d\n", _tree->root->data, _level);
      free(_tree->root);
      // copy the right child's root address to this tree's root
      _tree->root = rightChildRoot;
      return 1;
    }
    if (empty(_tree->root->rightChild)) {
      // free the right child tree wrapper
      free(_tree->root->rightChild);
      // save left child's root address in a variable
      Node *leftChildRoot = _tree->root->leftChild->root;
      // free left child tree wrapper
      free(_tree->root->leftChild);
      // free this tree's root node (actual deletion)
      printf("Deleting Node data %d at level %d\n", _tree->root->data, _level);
      free(_tree->root);
      // copy the left child's root address to this tree's root
      _tree->root = leftChildRoot;
      return 1;
    }
    // if none of left and right child are empty then codeflow comes here
    // we can copy a node's data to this tree root's data if
    // that node satisfies the binary tree condition
    // such node is found in the left subtrees of the right subtree of this tree
    Node *nodeToCopyFrom = _tree->root->rightChild->root;
    while (!empty(nodeToCopyFrom->leftChild))
      nodeToCopyFrom = nodeToCopyFrom->leftChild->root;
    // copy the data
    _tree->root->data = nodeToCopyFrom->data;

    // now delete that original node from where we copied (it is somewhere in
    // the rightchild)
    remove_element_tree(_tree->root->rightChild, nodeToCopyFrom->data, _level + 1);
    return 1;
  }
  if (_data < _tree->root->data)
    return remove_element_tree(_tree->root->leftChild, _data, _level + 1);
  return remove_element_tree(_tree->root->rightChild, _data, _level + 1);
}

void traverse_in_order(Binary_Search_Tree const *const _tree) {
  if (empty(_tree))
    return;

  traverse_in_order(_tree->root->leftChild);
  printf("%d ", _tree->root->data);
  traverse_in_order(_tree->root->rightChild);
}