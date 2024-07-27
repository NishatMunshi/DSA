#include "../include/queue_dynamic.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue_dynamic_node_struct {
    int data;
    struct queue_dynamic_node_struct *next;
} queue_dynamic_node;

struct queue_dynamic_struct {
    queue_dynamic_node *front, *rear;
    size_t size;
};

queue_dynamic *queue_dynamic_create() {
    queue_dynamic *queue = malloc(sizeof(struct queue_dynamic_struct));
    queue->front = queue->rear = malloc(sizeof(struct queue_dynamic_node_struct));
    queue->rear->next = NULL;
    queue->size = 0;
    return queue;
}
void queue_dynamic_push(queue_dynamic *queue, int data) {
    queue->rear->data = data;
    queue_dynamic_node *new_node = malloc(sizeof(struct queue_dynamic_node_struct));
    queue->rear->next = new_node;
    queue->rear = new_node;
    queue->size++;
}
int queue_dynamic_pop(queue_dynamic *queue) {
    if (queue->size == 0) {
        printf("[QUEUE_DYNAMIC ERROR]: queue underflow\n");
        return -1;
    }

    queue_dynamic_node *old_front = queue->front;
    int data = old_front->data;
    queue->front = old_front->next;
    free(old_front);
    queue->size--;
    return data;
}
void queue_dynamic_display(queue_dynamic *queue) {
    printf(
        "[QUEUE_DYNAMIC INFO]:\n"
        "       SIZE:     %zu\n"
        "       CONTENTS: {",
        queue->size);
    for (queue_dynamic_node *node = queue->front; node != queue->rear; node = node->next) {
        printf("%i%s", node->data, node->next == queue->rear ? "" : ", ");
    }
    printf("}\n");
}