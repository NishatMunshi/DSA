#include <stdio.h>
#include <stdlib.h>

struct Binary_Search_Tree;
typedef struct Node
{
    unsigned id;
    int data;
    struct Binary_Search_Tree *leftChild, *rightChild;
} Node;

// wrapper over root node
typedef struct Binary_Search_Tree
{
    Node *root;
} Binary_Search_Tree;

// checks if a tree is empty (ie its root is NULL)
int empty(Binary_Search_Tree const *const _tree) { return _tree->root == NULL; }

// allocates memory for an empty tree
Binary_Search_Tree *create_tree(void)
{
    Binary_Search_Tree *tree = (Binary_Search_Tree *)malloc(sizeof(Binary_Search_Tree));
    tree->root = NULL;

    return tree;
}

// leaves the argument as an empty tree
void delete_tree(Binary_Search_Tree *const _tree)
{
    if (empty(_tree))
        return;

    delete_tree(_tree->root->leftChild);  // first make the left child empty
    delete_tree(_tree->root->rightChild); // then make the right child empty

    // now that children are empty we can free its children and its root and mark it as empty
    free(_tree->root->leftChild);
    free(_tree->root->rightChild);
    free(_tree->root);
    _tree->root = NULL; // mark this tree as empty
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

unsigned node_count(Binary_Search_Tree const *const _tree)
{
    if (empty(_tree))
        return 0;
    if (leaf(_tree->root))
        return 1;
    return 1 + node_count(_tree->root->leftChild) +
           node_count(_tree->root->rightChild);
}

unsigned leaf_count(Binary_Search_Tree const *const _tree)
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
unsigned number_of_levels(Binary_Search_Tree const *const _tree)
{
    if (empty(_tree))
        return 0;
    if (leaf(_tree->root))
        return 1;
    return 1 + maximum(number_of_levels(_tree->root->leftChild),
                       number_of_levels(_tree->root->rightChild));
}

int insert_element(Binary_Search_Tree *const _tree, int const _data, unsigned const _level)
{
    // try to insert in this level
    if (empty(_tree))
    {
        _tree->root = create_node(_data);
        printf("Insertion done at level %d\n", _level);
        return 1;
    }

    // try to insert in left child
    int insertedInLeftChild = 0;
    if (_data < _tree->root->data)
        insertedInLeftChild = insert_element(_tree->root->leftChild, _data, _level + 1);
    if (insertedInLeftChild)
        return 1;

    // if failed, try to insert in right child
    return insert_element(_tree->root->rightChild, _data, _level + 1);
}

int remove_element(Binary_Search_Tree *const _tree, int const _data, unsigned const _level)
{
    if (empty(_tree))
        return 0;
    if (_data == _tree->root->data)
    {
        if (leaf(_tree->root))
        {
            // delete its empty subtrees
            delete_tree(_tree->root->leftChild);
            delete_tree(_tree->root->rightChild);

            printf("Deleting Node id %d at level %d\n", _tree->root->id, _level);
            // clear this tree's left child, right child  and root node
            delete_tree(_tree);
            return 1;
        }
        if (empty(_tree->root->leftChild))
        {
            // free the left child tree
            free(_tree->root->leftChild);
            // save right child's root address in a variable
            Node *rightChildRoot = _tree->root->rightChild->root;
            // free right child tree wrapper
            free(_tree->root->rightChild);
            // free this tree's root node (actual deletion)
            printf("Deleting Node id %d at level %d\n", _tree->root->id, _level);
            free(_tree->root);
            // copy the right child's root address to this tree's root
            _tree->root = rightChildRoot;
            return 1;
        }
        if (empty(_tree->root->rightChild))
        {
            // free the right child tree
            free(_tree->root->rightChild);
            // save left child's root address in a variable
            Node *leftChildRoot = _tree->root->leftChild->root;
            // free left child tree wrapper
            free(_tree->root->leftChild);
            // free this tree's root node (actual deletion)
            printf("Deleting Node id %d at level %d\n", _tree->root->id, _level);
            free(_tree->root);
            // copy the left child's root address to this tree's root
            _tree->root = leftChildRoot;
            return 1;
        }
        // if none of left and right child are empty then codeflow comes here
        // we can copy a node's data to this tree root's data if
        // that node satisfies the binary tree condition
        // such node is found in the left subtress of the right subtree of this tree
        Node *nodeToCopyFrom = _tree->root->rightChild->root;
        while (!empty(nodeToCopyFrom->leftChild))
            nodeToCopyFrom = nodeToCopyFrom->leftChild->root;
        // copy the data
        _tree->root->data = nodeToCopyFrom->data;

        // now delete that original node from where we copied (it is somewhere in the rightchild)
        remove_element(_tree->root->rightChild, nodeToCopyFrom->data, _level + 1);
        return 1;
    }
    if (_data < _tree->root->data)
        return remove_element(_tree->root->leftChild, _data, _level + 1);
    return remove_element(_tree->root->rightChild, _data, _level + 1);
}

void traverse_in_order(Binary_Search_Tree const *const _tree)
{
    if (empty(_tree))
        return;

    traverse_in_order(_tree->root->leftChild);
    printf("Visiting ID %d, data = %d\n", _tree->root->id, _tree->root->data);
    traverse_in_order(_tree->root->rightChild);
}

int balance_factor(Binary_Search_Tree const *const _tree)
{
    if (empty(_tree))
        return 0;
    int heightOfLeftChild = number_of_levels(_tree->root->leftChild);
    int heightOfRightChild = number_of_levels(_tree->root->rightChild);

    return heightOfLeftChild - heightOfRightChild;
}

void print_balance_factors(Binary_Search_Tree const *const _tree)
{
    if (empty(_tree))
        return;
    print_balance_factors(_tree->root->leftChild);
    printf("Node data %d, balance factor = %d\n", _tree->root->data, balance_factor(_tree));
    print_balance_factors(_tree->root->rightChild);
}

int height_balanced(Binary_Search_Tree const *const _tree)
{
    int heightOfLeftChild = number_of_levels(_tree->root->leftChild);
    int heightOfRightChild = number_of_levels(_tree->root->rightChild);
    return abs(heightOfLeftChild - heightOfRightChild) < 2;
}

unsigned two_to_the_power_of(unsigned const _exponent)
{
    if (_exponent == 0)
        return 1;
    return 2 * two_to_the_power_of(_exponent - 1);
}
void print_level_order(Binary_Search_Tree const *const _tree, unsigned const _totalNumberOfLevels, unsigned const _allowedDepth, unsigned const _level)
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
            for (unsigned i = 0; i < two_to_the_power_of(_totalNumberOfLevels - _level) - 1; i++)
                printf(" ");
            return;
        }
        else
        {
            printf("%d", _tree->root->data);
            for (unsigned i = 0; i < two_to_the_power_of(_totalNumberOfLevels - _level) - 1; i++)
                printf(" ");
        }
    }
    print_level_order(_tree->root->leftChild, _totalNumberOfLevels, _allowedDepth, _level + 1);
    print_level_order(_tree->root->rightChild, _totalNumberOfLevels, _allowedDepth, _level + 1);
    return;
}

void balance_height_by_LL_rotation(Binary_Search_Tree *const _tree)
{
    if (balance_factor(_tree) < 2)
        return; // LL rotation can't fix it

    // now we're sure balance factor is at least 2
    Node *pivot = _tree->root;
    Node *leftChildOfPivot = pivot->leftChild->root;
    Node *rightChildOfLeftChildOfPivot = pivot->leftChild->root->rightChild->root;

    _tree->root = leftChildOfPivot;
    _tree->root->rightChild->root = pivot;
    _tree->root->rightChild->root->leftChild->root = rightChildOfLeftChildOfPivot;


    balance_height_by_LL_rotation(_tree->root->leftChild);
    balance_height_by_LL_rotation(_tree);
    balance_height_by_LL_rotation(_tree->root->rightChild);

}

int main(void)
{
    Binary_Search_Tree *tree = create_tree();

    unsigned choice, nodeID;
    int data;
    do
    {
        printf("\nNode Count = %u, Leaf Count = %u, Number of Levels = %u\n",
               node_count(tree), leaf_count(tree), number_of_levels(tree));

        printf("\nMenu:\n");
        printf("1. Insert Element\n");
        printf("2. Delete Element\n");
        printf("3. Print Balance Factor\n");
        printf("4. Traverse In Order\n");
        printf("5. Balance by LL rotation\n");
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
            insert_element(tree, data, 0);
            break;
        case 2:
            printf("Enter the data to be deleted: ");
            scanf("%d", &data);
            printf("\n");
            if (!remove_element(tree, data, 0))
                printf("Deletion Failed.\n");
            break;
        case 3:
            print_balance_factors(tree);
            if (!height_balanced(tree))
                printf("Not ");
            printf("balanced\n");
            break;
        case 4:
            printf("\nTraversing In Order:\n");
            traverse_in_order(tree);
            break;
        case 5:
            balance_height_by_LL_rotation(tree);
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

        for (unsigned allowedDepth = 0; allowedDepth < number_of_levels(tree); allowedDepth++)
        {
            for (unsigned i = 0; i < two_to_the_power_of(number_of_levels(tree) - allowedDepth - 1) - 1; i++)
                printf(" ");
            print_level_order(tree, number_of_levels(tree), allowedDepth, 0);
            printf("\n");
        }

    } while (choice);

    delete_tree(tree);
    return 0;
}