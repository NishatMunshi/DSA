#include "include/linked_list_queue.h"

int main()
{
    Linked_List_Queue *queue = llqueue_create_queue();

    for (unsigned i = 0; i < 10; ++i)
        llqueue_push(queue, i);

    llqueue_display(queue);

    for (unsigned i = 0; i < 9; ++i)
        printf("%d ", llqueue_pop(queue));

    llqueue_display(queue);

    for (unsigned i = 0; i < 20; ++i)
        llqueue_push(queue, i);

    llqueue_display(queue);

    return 0;
}