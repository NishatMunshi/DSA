#pragma once

#include <stdlib.h> // for malloc
#include <assert.h> // for assert
#include <stdio.h>  // for printf

typedef struct SLL_Node
{
    int data;
    struct SLL_Node *next;
} SLL_Node;

typedef struct Singly_Linked_List
{
    SLL_Node *head;
    size_t size;
} Singly_Linked_List;

SLL_Node *sll_create_node(int const _data)
{
    SLL_Node *node = (SLL_Node *)malloc(sizeof(SLL_Node));

    node->data = _data;
    node->next = NULL;

    return node;
}

// creates an empty list
Singly_Linked_List *sll_create_list(void)
{
    Singly_Linked_List *list = (Singly_Linked_List *)malloc(sizeof(Singly_Linked_List));

    list->head = sll_create_node(INT_MIN);
    list->head->next = sll_create_node(INT_MIN);
    list->head->next->next = NULL;

    list->size = 0;

    return list;
}

// adds before the given index so that new node is now at the given index
void sll_add_before(Singly_Linked_List *const _list, size_t const _index, int const _data)
{
    assert(_index <= _list->size);

    // traverse to the position
    SLL_Node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    SLL_Node *nextNode = prevNode->next;
    SLL_Node *newNode = sll_create_node(_data);

    // create the new links
    prevNode->next = newNode;
    newNode->next = nextNode;

    ++_list->size;
}

// removes a node from the given index
int sll_remove(Singly_Linked_List *const _list, size_t const _index)
{
    assert(_index < _list->size);

    // traverse to the position
    SLL_Node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    SLL_Node *nextNode = prevNode->next->next;

    int returnValue = prevNode->next->data;
    free(prevNode->next);

    // create the new links
    prevNode->next = nextNode;

    --_list->size;

    return returnValue;
}

// returns a pointer to the data element at the given index
int *sll_at(Singly_Linked_List *const _list, size_t const _index)
{
    assert(_index < _list->size);

    // traverse to the position
    SLL_Node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    return &(prevNode->next->data);
}

// displays the list in one line
void sll_display(Singly_Linked_List const *const _list)
{
    printf("Sinlgy Linked List: ");
    for (SLL_Node *node = _list->head->next; node->next != NULL; node = node->next)
    {
        printf("%d ", node->data);
    }
    printf("\n");
}