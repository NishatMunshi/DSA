#include "../include/list.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node_struct {
    int data;
    struct list_node_struct *prev;
    struct list_node_struct *next;
} list_node;

struct list_struct {
    list_node *head;
    size_t size;
};

static list_node *list_node_create(int data) {
    list_node *node = malloc(sizeof(list_node));

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

// creates an empty list
list *list_create(void) {
    list *list = malloc(sizeof(list));

    list->head = list_node_create(__INT32_MAX__);

    list->head->prev = NULL;
    list->head->next = list_node_create(__INT32_MAX__);

    list->head->next->prev = list->head;
    list->head->next->next = NULL;

    list->size = 0;

    return list;
}

// adds before the given index so that new node is now at the given index
void list_add_before(list *list, size_t index, int data) {
    assert(index <= list->size);

    // traverse to the position
    list_node *prev_node = list->head;
    for (size_t i = 0; i < index; ++i) {
        prev_node = prev_node->next;
    }
    list_node *next_node = prev_node->next;
    list_node *new_node = list_node_create(data);

    // create the new links
    prev_node->next = new_node;
    new_node->prev = prev_node;
    new_node->next = next_node;
    next_node->prev = new_node;

    ++list->size;
}

// removes a node from the given index
int list_remove(list *list, size_t index) {
    assert(index < list->size);

    // traverse to the position
    list_node *prev_node = list->head;
    for (size_t i = 0; i < index; ++i) {
        prev_node = prev_node->next;
    }
    list_node *next_node = prev_node->next->next;

    int ret_val = prev_node->next->data;
    free(prev_node->next);

    // create the new links
    prev_node->next = next_node;
    next_node->prev = prev_node;

    --list->size;

    return ret_val;
}