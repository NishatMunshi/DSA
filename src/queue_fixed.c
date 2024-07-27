#include "../include/queue_fixed.h"

#include <stdio.h>
#include <stdlib.h>

struct queue_fixed_struct {
    int *items;
    size_t front, rear;
    size_t size;
    size_t capacity;
};

queue_fixed *queue_fixed_create(size_t capacity) {
    queue_fixed *queue = malloc(sizeof(struct queue_fixed_struct));
    queue->items = malloc(capacity * sizeof(queue->items[0]));
    queue->front = queue->rear = 0;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void queue_fixed_push(queue_fixed *queue, int data) {
    if (queue->size >= queue->capacity) {
        printf("[QUEUE_FIXED ERROR]: queue overflow\n");
        return;
    }
    queue->rear %= queue->capacity;
    queue->items[queue->rear++] = data;
    queue->size++;
}

int queue_fixed_pop(queue_fixed *queue) {
    if (queue->size == 0) {
        printf("[QUEUE_FIXED ERROR]: queue underflow\n");
        return -1;
    }
    queue->front %= queue->capacity;
    queue->size--;
    return queue->items[queue->front++];
}

void queue_fixed_display(queue_fixed *queue) {
    printf(
        "[QUEUE_FIXED INFO]:\n"
        "       CAPACITY: %zu\n"
        "       FRONT:    %zu\n"
        "       REAR:     %zu\n"
        "       SIZE:     %zu\n"
        "       CONTENTS: {",
        queue->capacity, queue->front, queue->rear, queue->size);

    for (size_t i = queue->front, item = 0; item < queue->size; ++i, ++item) {
        printf("%i%s", queue->items[i % queue->capacity], item == queue->size - 1 ? "" : ", ");
    }
    printf("}\n");
}
