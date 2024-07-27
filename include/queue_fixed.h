#ifndef DSA_QUEUE_FIXED_H
#define DSA_QUEUE_FIXED_H

#include <stddef.h>

typedef struct queue_fixed_struct queue_fixed;

queue_fixed *queue_fixed_create(size_t capacity);
void         queue_fixed_push( queue_fixed *queue ,int data);
int          queue_fixed_pop(queue_fixed *queue);
void         queue_fixed_display(queue_fixed *queue);

#endif // DSA_QUEUE_FIXED_H