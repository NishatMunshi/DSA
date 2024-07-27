#ifndef DSA_QUEUE_DYNAMIC_H
#define DSA_QUEUE_DYNAMIC_H

typedef struct queue_dynamic_struct queue_dynamic;

queue_dynamic *queue_dynamic_create();
void           queue_dynamic_push(queue_dynamic *queue ,int data);
int            queue_dynamic_pop(queue_dynamic *queue);
void           queue_dynamic_display(queue_dynamic *queue);

#endif // DSA_QUEUE_DYNAMIC_H