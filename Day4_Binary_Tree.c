#include <stdio.h>
#include <stdlib.h>

struct Binary_Tree;
typedef struct Node
{
  unsigned id;
  int data;
  struct Binary_Tree *leftChild, *rightChild;
} Node;
typedef struct Binary_Tree
{
  Node *root;
} Binary_Tree;
// checks if a tree is empty (ie its root is NULL)
int empty(Binary_Tree const *const _tree) { return _tree->root == NULL; }
// allocates memory for an empty tree
Binary_Tree *create_tree(void)
{
  Binary_Tree *tree = (Binary_Tree *)malloc(sizeof(Binary_Tree));
  tree->root = NULL;

  return tree;
}
// allocates memory for a new node with a brand new id and two empty subtrees
Node *create_node(int const _data)
{
  static unsigned nodeID = 0;

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->id = nodeID++;
  newNode->data = _data;
  newNode->leftChild = create_tree();
  newNode->rightChild = create_tree();

  return newNode;
}

// checks if a node is a leaf node or not
int leaf(Node const *const _node)
{
  return empty(_node->leftChild) && empty(_node->rightChild);
}

unsigned node_count(Binary_Tree const *const _tree)
{
  if (empty(_tree))
    return 0;
  if (leaf(_tree->root))
    return 1;
  return 1 + node_count(_tree->root->leftChild) +
         node_count(_tree->root->rightChild);
}

unsigned leaf_count(Binary_Tree const *const _tree)
{
  if (empty(_tree))
    return 0;
  if (leaf(_tree->root))
    return 1;
  return leaf_count(_tree->root->leftChild) +
         leaf_count(_tree->root->rightChild);
}

unsigned maximum(unsigned const _a, unsigned const _b)
{
  return _a > _b ? _a : _b;
}
unsigned number_of_levels(Binary_Tree const *const _tree)
{
  if (empty(_tree))
    return 0;
  if (leaf(_tree->root))
    return 1;
  return 1 + maximum(number_of_levels(_tree->root->leftChild),
                     number_of_levels(_tree->root->rightChild));
}

// leaves the argument as an empty tree
void delete_tree(Binary_Tree *const _tree)
{
  if (empty(_tree))
    return;

  delete_tree(_tree->root->leftChild);  // first make the left child empty
  delete_tree(_tree->root->rightChild); // then make the right child empty

  // now that children are empty we can free its children and its root and mark
  // it as empty
  printf("Freeing tree %x\n", _tree->root->leftChild);
  free(_tree->root->leftChild);
  printf("Freeing tree %x\n", _tree->root->rightChild);
  free(_tree->root->rightChild);
  printf("Freeing root id %d\n", _tree->root->id);
  free(_tree->root);
  _tree->root = NULL; // mark this tree as empty
}

void traverse_pre_order(Binary_Tree const *const _tree)
{
  if (empty(_tree))
    return;

  printf("Visiting ID %d, data = %d\n", _tree->root->id, _tree->root->data);
  traverse_pre_order(_tree->root->leftChild);
  traverse_pre_order(_tree->root->rightChild);
}
void traverse_in_order(Binary_Tree const *const _tree)
{
  if (empty(_tree))
    return;

  traverse_in_order(_tree->root->leftChild);
  printf("Visiting ID %d, data = %d\n", _tree->root->id, _tree->root->data);
  traverse_in_order(_tree->root->rightChild);
}
void traverse_post_order(Binary_Tree const *const _tree)
{
  if (empty(_tree))
    return;

  traverse_post_order(_tree->root->leftChild);
  traverse_post_order(_tree->root->rightChild);
  printf("Visiting ID %d, data = %d\n", _tree->root->id, _tree->root->data);
}

int insert_element(Binary_Tree *const _tree, int const _data,
                   unsigned const _allowedDepth, unsigned const _level)
{
  // try to insert in this level
  int insertedInThisLevel = 0;
  if (empty(_tree))
  {
    _tree->root = create_node(_data);
    printf("Insertion done at level %d\n", _level);
    insertedInThisLevel = 1; // successful insertion
    return 1;
  }

  // if allowed depth to search is reached don't dig deeper
  if (_allowedDepth == 0)
    return insertedInThisLevel;

  // if insertion in this level was a failure and we still have depth to search,
  // try to insert in the left child
  if (insert_element(_tree->root->leftChild, _data, _allowedDepth - 1,
                     _level + 1))
    return 1;

  // if insertion in leftChild was a failure try to insert in the right child,
  // and if that fails return 0
  return insert_element(_tree->root->rightChild, _data, _allowedDepth - 1,
                        _level + 1);
}
int remove_element(Binary_Tree *const _tree, unsigned const _id)
{
  if (empty(_tree))
    return 0; // failure

  // if this tree's root's id matches then delete this tree
  if (_tree->root->id == _id)
  {
    delete_tree(_tree);
    printf("Deletion Successful\n");
    return 1; // success
  }

  // if not then try to delete in left child
  if (remove_element(_tree->root->leftChild, _id))
    return 1;

  // if unsuccessful try to delete in right child, if that fails return failure
  return remove_element(_tree->root->rightChild, _id);
}

int strictly_binary(Binary_Tree const *const _tree)
{
  // empty tree is strictly binary
  if (empty(_tree))
    return 1;
  // leaf itself is a strictly binary tree
  if (leaf(_tree->root))
    return 1;

  // non leaf nodes should not have exactly 1 non empty subtree
  if (empty(_tree->root->leftChild) && !empty(_tree->root->rightChild))
    return 0;
  if (!empty(_tree->root->leftChild) && empty(_tree->root->rightChild))
    return 0;

  return strictly_binary(_tree->root->leftChild) &&
         strictly_binary(_tree->root->rightChild);
}
int complete_binary(Binary_Tree const *const _tree, unsigned const _depth,
                    unsigned const _maxDepth)
{
  // firstly it has to be strictly binary
  if (!strictly_binary(_tree))
    return 0;
  // empty tree is complete binary
  if (empty(_tree))
    return 1;
  // if we find a leaf at depth < max depth then immediately return 0
  if (leaf(_tree->root))
  {
    if (_depth < _maxDepth)
      return 0;
  }
  return complete_binary(_tree->root->leftChild, _depth + 1, _maxDepth) &&
         complete_binary(_tree->root->rightChild, _depth + 1, _maxDepth);
}
int almost_complete_binary(Binary_Tree const *const _tree, unsigned const _depth,
                           unsigned const _maxDepth)
{
  // empty tree is almost complete binary (base case)
  if (empty(_tree))
    return 1;

  // another base case
  // if (leaf(_tree->root) && _depth == _maxDepth)
  //   return 1;

  // condition 1
  if ((empty(_tree->root->leftChild) || empty(_tree->root->rightChild)) && _depth < _maxDepth - 1)
    return 0;

  // condition  2
  if (_depth!= _maxDepth && number_of_levels(_tree->root->rightChild) == _maxDepth - _depth)
  {
    // condition 2.1
    if (empty(_tree->root->leftChild))
      return 0;

    // condition 2.2
    int condition = complete_binary(_tree->root->leftChild, _depth + 1, _maxDepth);
    if (!condition)
      return 0;
  }

  int left = almost_complete_binary(_tree->root->leftChild, _depth + 1, _maxDepth);
  int right = almost_complete_binary(_tree->root->rightChild, _depth + 1, _maxDepth);

  return left && right;
}

unsigned two_to_the_power_of(unsigned const _exponent)
{
  if (_exponent == 0)
    return 1;
  return 2 * two_to_the_power_of(_exponent - 1);
}
void print_level_order(Binary_Tree const *const _tree,
                       unsigned const _totalNumberOfLevels,
                       unsigned const _allowedDepth, unsigned const _level)
{
  if (empty(_tree) && _level != _allowedDepth)
    return;
  if (_level > _allowedDepth)
    return;
  if (_level == _allowedDepth)
  {
    if (empty(_tree))
    {
      printf(".");
      for (unsigned i = 0;
           i < two_to_the_power_of(_totalNumberOfLevels - _level) - 1; i++)
        printf(" ");
      return;
    }
    else
    {
      printf("%d", _tree->root->data);
      for (unsigned i = 0;
           i < two_to_the_power_of(_totalNumberOfLevels - _level) - 1; i++)
        printf(" ");
    }
  }
  print_level_order(_tree->root->leftChild, _totalNumberOfLevels, _allowedDepth,
                    _level + 1);
  print_level_order(_tree->root->rightChild, _totalNumberOfLevels,
                    _allowedDepth, _level + 1);
  return;
}

int main(void)
{
  Binary_Tree *tree = create_tree();

  unsigned choice, nodeID;
  int data;
  do
  {
    printf("\nNode Count = %u, Leaf Count = %u, Number of Levels = %u\n",
           node_count(tree), leaf_count(tree), number_of_levels(tree));

    printf("\nMenu:\n");
    printf("1. Insert Element\n");
    printf("2. Pre Order Traversal\n");
    printf("3. In Order Traversal\n");
    printf("4. Post Order Traversal\n");
    printf("5. Check Type of Binary_Tree\n");
    printf("6. Delete a Subtree\n");
    printf("0. Exit\n\n");

    printf("Enter your choice: ");
    scanf("%u", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
      printf("Enter the data to be inserted: ");
      scanf("%d", &data);
      printf("\n");
      unsigned nextPossibleInsertionDepth = 0; // reset
      while (!insert_element(tree, data, nextPossibleInsertionDepth, 0))
        nextPossibleInsertionDepth++;
      break;
    case 2:
      printf("\nTraversing Pre Order:\n");
      traverse_pre_order(tree);
      break;
    case 3:
      printf("\nTraversing In Order:\n");
      traverse_in_order(tree);
      break;
    case 4:
      printf("\nTraversing Post Order:\n");
      traverse_post_order(tree);
      break;
    case 5:
      printf("Binary_Tree is:\n");
      if (!strictly_binary(tree))
        printf("Not ");
      printf("Strictly Binary\n");
      if (!complete_binary(tree, 0, number_of_levels(tree) - 1))
        printf("Not ");
      printf("Complete Binary\n");
      if (!almost_complete_binary(tree, 0, number_of_levels(tree) - 1))
        printf("Not ");
      printf("Almost Complete Binary\n");
      break;
    case 6:
      printf("Enter the root ID to remove: ");
      scanf("%d", &nodeID);
      printf("\n");
      if (!remove_element(tree, nodeID))
        printf("Deletion failed.\n");
      break;
    case 0:
      printf("Exiting Program ...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
      break;
    }

    // printing the tree
    printf("\nTree:\n");
    for (unsigned allowedDepth = 0; allowedDepth < number_of_levels(tree);
         allowedDepth++)
    {
      for (unsigned i = 0;
           i <
           two_to_the_power_of(number_of_levels(tree) - allowedDepth - 1) - 1;
           i++)
        printf(" ");
      print_level_order(tree, number_of_levels(tree), allowedDepth, 0);
      printf("\n");
    }
  } while (choice);

  delete_tree(tree);
  return 0;
}