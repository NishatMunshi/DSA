#ifndef DSA_LIST_H
#define DSA_LIST_H

#include <stddef.h>

typedef struct list_struct list;

list *list_create(void);
void  list_add_before(list *list, size_t index, int data);
int   list_remove(list *list, size_t index);

#endif // DSA_LIST_H
