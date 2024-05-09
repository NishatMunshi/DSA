#pragma once

#include <stdlib.h> // for malloc
#include <assert.h> // for assert
#include <stdio.h>  // for printf

typedef struct LLQueue_Node
{
    int data;
    struct LLQueue_Node *next;
} LLQueue_Node;

typedef struct Linked_List_Queue
{
    LLQueue_Node *head, *tail;
    size_t size;
} Linked_List_Queue;

Linked_List_Queue *llqueue_create_queue(void)
{
    Linked_List_Queue *queue = (Linked_List_Queue *)malloc(sizeof(Linked_List_Queue));
    queue->head = (LLQueue_Node *)malloc(sizeof(LLQueue_Node));
    queue->tail = (LLQueue_Node *)malloc(sizeof(LLQueue_Node));

    queue->head->next = queue->tail;
    queue->tail->next = NULL;

    queue->size = 0;
}

void llqueue_push(Linked_List_Queue *const _queue, int const _data)
{
    _queue->tail->data = _data;

    LLQueue_Node *newNode = (LLQueue_Node *)malloc(sizeof(LLQueue_Node));
    _queue->tail->next = newNode;
    newNode->next = NULL;
    _queue->tail = newNode;

    ++_queue->size;
}

int llqueue_pop(Linked_List_Queue *const _queue)
{
    assert(_queue->size > 0);

    LLQueue_Node *toFree = _queue->head;
    int toReturn = toFree->next->data;
    _queue->head = toFree->next;
    free(toFree);
    --_queue->size;

    return toReturn;
}

void llqueue_display(Linked_List_Queue const *const _queue)
{
    printf("Linked List Queue: ");
    for (LLQueue_Node *node = _queue->head->next; node->next != NULL; node = node->next)
    {
        printf("%d ", node->data);
    }
    printf("\n");
}