#pragma once

#include "linked_list_queue.h"

typedef Linked_List_Queue Min_Priority_Queue;

Min_Priority_Queue *minpriorityqueue_create_queue(void)
{
    Linked_List_Queue *queue = llqueue_create_queue();

    queue->head->data = INT_MIN;
    queue->tail->data = INT_MAX;

    return queue;
}

void minpriorityqueue_push(Min_Priority_Queue *const _queue, int const _data)
{
    LLQueue_Node *prevNode;
    for (prevNode = _queue->head; prevNode->next != _queue->tail && prevNode->next->data < _data; prevNode = prevNode->next)
        ;

    LLQueue_Node *nextNode = prevNode->next;
    LLQueue_Node *newNode = (LLQueue_Node *)malloc(sizeof(LLQueue_Node));
    newNode->data = _data;

    prevNode->next = newNode;
    newNode->next = nextNode;

    ++_queue->size;

}
int minpriorityqueue_pop(Min_Priority_Queue *const _queue)
{
    return llqueue_pop(_queue);
}

void minpriorityqueue_display(Min_Priority_Queue const *const _queue)
{
    llqueue_display(_queue);
}
