#pragma once

#include "singly_linked_list.h"

typedef Singly_Linked_List Linked_List_Stack;

Linked_List_Stack *llstack_create_stack(void)
{
    return sll_create_list();
}
void llstack_push(Linked_List_Stack *const _stack, int const _data)
{
    sll_add_before(_stack, 0u, _data);
}

int llstack_pop(Linked_List_Stack *const _stack)
{
    return sll_remove(_stack, 0u);
}

void llstack_display(Linked_List_Stack const *const _stack)
{
    printf("Linked List Stack: ");
    for (SLL_Node *node = _stack->head->next; node->next != NULL; node = node->next)
    {
        printf("%d ", node->data);
    }
    printf("\n");
}