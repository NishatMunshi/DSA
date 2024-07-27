#include "../include/avl_tree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct avl_tree_node_struct {
    int data;
    avl_tree *left, *right;
} avl_tree_node;

// wrapper around root node
struct avl_tree_struct {
    avl_tree_node *root;
    size_t size;
    size_t height;
};

// checks if a tree is empty (ie its root is NULL)
static int avl_tree_empty(avl_tree *tree) { return tree->root == NULL; }
// checks if a non empty tree is a leaf or not
static int avl_tree_leaf(avl_tree *tree) {
    return !(avl_tree_empty(tree)) && avl_tree_empty(tree->root->left) && avl_tree_empty(tree->root->right);
}
static int avl_tree_has_left_child(avl_tree *tree) {
    return !(avl_tree_empty(tree)) && !avl_tree_empty(tree->root->left);
}
static int avl_tree_has_right_child(avl_tree *tree) {
    return !(avl_tree_empty(tree)) && !avl_tree_empty(tree->root->right);
}
static long avl_tree_balance_factor(avl_tree *tree) {
    if (avl_tree_empty(tree)) {
        return 0;
    }
    return tree->root->left->height - tree->root->right->height;
}

#define ABS(x) (((x) >= 0) ? (x) : (-(x)))

static int avl_tree_balanced(avl_tree *tree) {
    return ABS(avl_tree_balance_factor(tree)) < 2;
}
static void avl_tree_update_size(avl_tree *tree) {
    if (avl_tree_empty(tree)) {
        tree->size = 0;
        return;
    }

    tree->size = 1 + tree->root->left->size + tree->root->right->size;
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static void avl_tree_update_height(avl_tree *tree) {
    if (avl_tree_empty(tree)) {
        tree->size = 0;
        return;
    }
    tree->height = 1 + MAX(tree->root->left->height, tree->root->right->height);
}

static void avl_tree_ll_rotate(avl_tree *tree) {
    // make copies of some information (only copying some integers and pointers, not a big deal)
    avl_tree right_of_left = *(tree->root->left->root->right);
    avl_tree right = *(tree->root->right);
    avl_tree left = *(tree->root->left);
    avl_tree this_tree = *(tree);

    // now we can copy informations to correct places
    *(tree) = left;
    *(tree->root->right) = this_tree;
    *(tree->root->right->root->right) = right;
    *(tree->root->right->root->left) = right_of_left;

    avl_tree_update_size(tree->root->right);
    avl_tree_update_height(tree->root->right);
    avl_tree_update_size(tree);
    avl_tree_update_height(tree);
}

static void avl_tree_rr_rotate(avl_tree *tree) {
    // make copies of some information (only copying some integers and pointers, not a big deal)
    avl_tree left_of_right = *(tree->root->right->root->left);
    avl_tree left = *(tree->root->left);
    avl_tree right = *(tree->root->right);
    avl_tree this_tree = *(tree);

    // now we can copy informations to correct places
    *(tree) = right;
    *(tree->root->left) = this_tree;
    *(tree->root->left->root->left) = left;
    *(tree->root->left->root->right) = left_of_right;

    avl_tree_update_size(tree->root->left);
    avl_tree_update_height(tree->root->left);
    avl_tree_update_size(tree);
    avl_tree_update_height(tree);
}

static void avl_tree_lr_rotate(avl_tree *tree) {
    avl_tree_rr_rotate(tree->root->left);
    avl_tree_ll_rotate(tree);
}

static void avl_tree_rl_rotate(avl_tree *tree) {
    avl_tree_ll_rotate(tree->root->right);
    avl_tree_rr_rotate(tree);
}

// allocates memory for a new node with two empty subtrees
static avl_tree_node *avl_tree_create_node(int data) {
    avl_tree_node *node = (avl_tree_node *)malloc(sizeof(avl_tree_node));
    node->data = data;
    node->left = avl_tree_create();
    node->right = avl_tree_create();

    return node;
}

// allocates memory for an empty tree
avl_tree *avl_tree_create(void) {
    avl_tree *tree = (avl_tree *)malloc(sizeof(avl_tree));
    tree->root = NULL;
    tree->height = 0;
    tree->size = 0;

    return tree;
}

void avl_tree_insert(avl_tree *tree, int data) {
    if (avl_tree_empty(tree)) {
        tree->root = avl_tree_create_node(data);
    } else if (data < tree->root->data) {
        avl_tree_insert(tree->root->left, data);

        // necessary rotations LL or LR
        if (!avl_tree_balanced(tree)) {
            if (data < tree->root->left->root->data) {
                avl_tree_ll_rotate(tree);
            } else {
                avl_tree_lr_rotate(tree);
            }
        }
    } else {
        avl_tree_insert(tree->root->right, data);

        // necessary rotations RR or RL
        if (!avl_tree_balanced(tree)) {
            if (data < tree->root->right->root->data) {
                avl_tree_rl_rotate(tree);
            } else {
                avl_tree_rr_rotate(tree);
            }
        }
    }

    avl_tree_update_size(tree);
    avl_tree_update_height(tree);
}

void avl_tree_remove(avl_tree *tree, int data) {
    assert(!avl_tree_empty(tree));

    if (tree->root->data == data) {
        if (avl_tree_leaf(tree)) {
            free(tree->root->left);
            free(tree->root->right);
            free(tree->root);
            tree->root = NULL;
        } else if (avl_tree_has_left_child(tree) && !avl_tree_has_right_child(tree)) {
            avl_tree left = *(tree->root->left);
            free(tree->root->left);
            free(tree->root->right);
            free(tree->root);
            tree->root = NULL;

            *tree = left;
        } else if (avl_tree_has_right_child(tree) && !avl_tree_has_left_child(tree)) {
            avl_tree right = *(tree->root->right);
            free(tree->root->left);
            free(tree->root->right);
            free(tree->root);
            tree->root = NULL;

            *tree = right;
        } else {
            // find inorder successor
            avl_tree *inorder_successor = tree->root->right;
            while (!avl_tree_empty(inorder_successor->root->left)) {
                inorder_successor = inorder_successor->root->left;
            }

            tree->root->data = inorder_successor->root->data;
            avl_tree_remove(tree->root->right, tree->root->data);
        }
    } else if (data < tree->root->data) {
        avl_tree_remove(tree->root->left, data);
        if (!avl_tree_balanced(tree)) {
            if (avl_tree_balance_factor(tree->root->right) <= 0) {
                avl_tree_rr_rotate(tree);
            } else {
                avl_tree_rl_rotate(tree);
            }
        }
    } else {
        avl_tree_remove(tree->root->right, data);
        if (avl_tree_balanced(tree)) {
            if (avl_tree_balance_factor(tree->root->left) >= 0) {
                avl_tree_ll_rotate(tree);
            } else {
                avl_tree_lr_rotate(tree);
            }
        }
    }
    avl_tree_update_size(tree);
    avl_tree_update_height(tree);
}

void avl_tree_traverse_inorder(avl_tree *tree) {
    if (avl_tree_empty(tree)) {
        return;
    }

    avl_tree_traverse_inorder(tree->root->left);
    printf("%i ", tree->root->data);
    avl_tree_traverse_inorder(tree->root->right);
}

void avl_tree_fill_array_inorder(avl_tree *tree, int *array) {
    if (avl_tree_empty(tree)) {
        return;
    }
    static size_t next_free_index = 0;
    avl_tree_fill_array_inorder(tree->root->left, array);
    array[next_free_index++] = tree->root->data;
    avl_tree_fill_array_inorder(tree->root->right, array);
}
