#pragma once

#include <stdlib.h> // for malloc
#include <assert.h> // for assert
#include <stdio.h>  // for printf

typedef struct DLL_Node
{
    int data;
    struct DLL_Node *prev;
    struct DLL_Node *next;
} DLL_Node;

typedef struct Doubly_Linked_List
{
    DLL_Node *head;
    size_t size;
} Doubly_Linked_List;

DLL_Node *dll_create_node(int const _data)
{
    DLL_Node *node = (DLL_Node *)malloc(sizeof(DLL_Node));

    node->data = _data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

// creates an empty list
Doubly_Linked_List *dll_create_list(void)
{
    Doubly_Linked_List *list = (Doubly_Linked_List *)malloc(sizeof(Doubly_Linked_List));

    list->head = dll_create_node(INT_MIN);

    list->head->prev = NULL;
    list->head->next = dll_create_node(INT_MIN);

    list->head->next->prev = list->head;
    list->head->next->next = NULL;

    list->size = 0;

    return list;
}

// adds before the given index so that new node is now at the given index
void dll_add_before(Doubly_Linked_List *const _list, size_t const _index, int const _data)
{
    assert(_index <= _list->size);

    // traverse to the position
    DLL_Node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    DLL_Node *nextNode = prevNode->next;
    DLL_Node *newNode = dll_create_node(_data);

    // create the new links
    prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = nextNode;
    nextNode->prev = newNode;

    ++_list->size;
}

// removes a node from the given index
int dll_remove(Doubly_Linked_List *const _list, size_t const _index)
{
    assert(_index < _list->size);

    // traverse to the position
    DLL_Node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    DLL_Node *nextNode = prevNode->next->next;

    int returnValue = prevNode->next->data;
    free(prevNode->next);
    
    // create the new links
    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    --_list->size;

    return returnValue;
}

// returns a pointer to the data element at the given index
int *dll_at(Doubly_Linked_List *const _list, size_t const _index)
{
    assert(_index < _list->size);

    // traverse to the position
    DLL_Node *prevNode = _list->head;
    for (size_t index = 0; index < _index; ++index)
    {
        prevNode = prevNode->next;
    }
    return &(prevNode->next->data);
}

// displays the list in one line
void dll_display(Doubly_Linked_List const *const _list)
{
    printf("Doubly Linked List: ");
    for (DLL_Node *node = _list->head->next; node->next != NULL; node = node->next)
    {
        printf("%d ", node->data);
    }
    printf("\n");
}