#pragma once

#include <stdlib.h> // for malloc
#include <assert.h> // for assert
#include <stdio.h>  // for printf

typedef struct Fixed_Memory_Queue
{
    int *items;
    size_t rear;  // one after the rear
    size_t front; // front
    size_t capacity;
    size_t size;
} Fixed_Memory_Queue;

Fixed_Memory_Queue *fmqueue_create_queue(size_t const _maxSize)
{
    Fixed_Memory_Queue *queue = (Fixed_Memory_Queue *)malloc(sizeof(Fixed_Memory_Queue));

    queue->items = (int *)malloc(_maxSize * sizeof(int));
    queue->capacity = _maxSize;
    queue->size = 0;
    queue->rear = 0;
    queue->front = 0;

    return queue;
}

void fmqueue_push(Fixed_Memory_Queue *const _queue, int const _data)
{
    // check overflow
    assert(_queue->size < _queue->capacity);

    _queue->rear %= _queue->capacity;
    _queue->items[_queue->rear++] = _data;

    ++_queue->size;
}

int fmqueue_pop(Fixed_Memory_Queue *const _queue)
{
    // check underflow
    assert(_queue->size > 0);

    _queue->front %= _queue->capacity;
    --_queue->size;

    return _queue->items[_queue->front++];
}

void fmqueue_display(Fixed_Memory_Queue const *const _queue)
{
    printf("Fixed Memory Queue: ");
    for (unsigned count = 0, index = _queue->front; count < _queue->size; ++count, ++index)
    {
        printf("%d ", _queue->items[index % _queue->capacity]);
    }
    printf("\n");
}