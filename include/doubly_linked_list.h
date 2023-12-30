#pragma once 

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *prev, *next;
} Node;

typedef struct Doubly_Linked_List
{
    Node *head, *tail;
    size_t size;
} Doubly_Linked_List;

void init_list(Doubly_Linked_List *const _list)
{
    _list->head = (Node *)malloc(sizeof(Node));
    _list->tail = (Node *)malloc(sizeof(Node));

    _list->head->prev = NULL;
    _list->head->next = _list->tail;
    _list->tail->prev = _list->head;
    _list->tail->next = NULL;

    _list->size = 0;
}

void add_before(Doubly_Linked_List *const _list, size_t const _position, int const _data)
{
    assert(_list->size >= _position);

    Node *prev = _list->head;
    for (size_t index = 0; index < _position; ++index)
    {
        prev = prev->next;
    }
    Node *next = prev->next;

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = _data;

    prev->next = newNode;
    newNode->prev = prev;
    newNode->next = next;
    next->prev = newNode;

    ++_list->size;
}

void display(Doubly_Linked_List const *const _list)
{
    Node *node = _list->head;
    for (size_t index = 0; index < _list->size; ++index)
    {
        node = node->next;
        printf("%d ", node->data);
    }
}


void remove_elem(Doubly_Linked_List *const _list, size_t const _position)
{
    assert(_list->size > _position);

    Node *prev = _list->head;
    for (size_t index = 0; index < _position; ++index)
    {
        prev= prev->next;
    }
    Node *next = prev->next->next;
    free(prev->next);

    prev->next = next;
    next->prev = prev;

    --_list->size;
}

void display_reverse(Doubly_Linked_List const * const _list)
{
    Node *node = _list->tail;
    for (size_t index = 0; index < _list->size; ++index)
    {
        node = node->prev;
        printf("%d ", node->data);
    }
}