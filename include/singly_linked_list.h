#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Singly_Linked_List
{
    Node *head;
    size_t size;
} Singly_Linked_List;

void init_list(Singly_Linked_List *const _list)
{
    _list->head = (Node *)malloc(sizeof(Node));
    _list->head->next = (Node *)malloc(sizeof(Node));
    _list->head->next->next = NULL;

    _list->size = 0;
}

void add_before(Singly_Linked_List *const _list, size_t const _position, int const _data)
{
    assert(_list->size >= _position);

    Node *prev = _list->head;
    for (size_t index  = 0; index < _position; ++index)
    {
        prev = prev->next;
    }
    Node *next = prev->next;
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = _data;
    prev->next = newNode;
    newNode->next = next;

    ++_list->size;
}

void display(Singly_Linked_List const *const _list)
{
    Node *node = _list->head;
    for (size_t index = 0; index < _list->size; ++index)
    {
        node = node->next;
        printf("%c ", node->data);
    }
    printf("\n");
}

void remove_elem(Singly_Linked_List *const _list, size_t const _position)
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

    --_list->size;
}

int *at(Singly_Linked_List * const _list, unsigned const _index ){
    assert(_index < _list->size);

    Node *node = _list->head;

    for (size_t index = 0; index < _index; ++index)
    {
        node = node->next;
    }
    return &(node->next->data);
}