#include "../include/list.h"

#include <stdlib.h> 
#include <assert.h> 
#include <stdio.h>  
#include <stddef.h>

typedef struct list_node_struct
{
    int data;
    struct list_node_struct *prev;
    struct list_node_struct *next;
} list_node;

struct list
{
    list_node *head;
    size_t size;
};

list_node *list_node_create(int const _data)
{
    list_node *node = (list_node *)malloc(sizeof(list_node));

    node->data = _data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

// creates an empty list
list *list_create_list(void)
{
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
void list_add_before(list *const _list, size_t const _index, int const _data)
{
    assert(_index <= _list->size);

    // traverse to the position
    list_node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    list_node *nextNode = prevNode->next;
    list_node *newNode = list_create_node(_data);

    // create the new links
    prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = nextNode;
    nextNode->prev = newNode;

    ++_list->size;
}

// removes a node from the given index
int list_remove(list *const _list, size_t const _index)
{
    assert(_index < _list->size);

    // traverse to the position
    list_node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    list_node *nextNode = prevNode->next->next;

    int returnValue = prevNode->next->data;
    free(prevNode->next);
    
    // create the new links
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    --_list->size;

    return returnValue;
}