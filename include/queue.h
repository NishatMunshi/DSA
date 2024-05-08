#include <stdio.h>
#include <stdlib.h>

typedef struct Queue_Node
{
    void * data;
    struct Queue_Node *next;
} Queue_Node;

typedef struct Queue
{
    Queue_Node *head, *tail;
    unsigned size;
} Queue;

void initialize(Queue *const _queue)
{
    _queue->head = (Queue_Node *)malloc(sizeof(Queue_Node));
    _queue->head->next = (Queue_Node *)malloc(sizeof(Queue_Node));
    _queue->tail = _queue->head->next;
    _queue->tail->next = NULL;

    _queue->size = 0;
}

void queue_insert_element(Queue *const _queue, void * const _item)
{
    _queue->tail->data = _item;

    Queue_Node *newNode = (Queue_Node *)malloc(sizeof(Queue_Node));
    _queue->tail->next = newNode;
    newNode->next = NULL;
    _queue->tail = newNode;

    ++_queue->size;
}

void * queue_remove_element(Queue *const _queue)
{
    if (_queue->size == 0)
    {
        printf("Underflow Error!\n");
        return NULL;
    }
    Queue_Node *toFree = _queue->head;
    void * toReturn = toFree->next->data;
    _queue->head = toFree->next;
    free(toFree);
    --_queue->size;

    return toReturn;
}

void display(Queue const *const _queue)
{
    printf("\n");
    if (_queue->size == 0)
    {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue Elements: ");
    for (Queue_Node *node = _queue->head; node->next != _queue->tail; node = node->next)
    {
        printf("%d->", node->next->data);
    }
    printf("X\n");
}