#include<singly_linked_list.h>

typedef struct LL_stack
{
    Singly_Linked_List *list;
}LL_stack;

 void init_LL_stack(LL_stack *const _stack)
{
    _stack->list = (Singly_Linked_List *)malloc(sizeof(Singly_Linked_List));
    init_list(_stack->list);
}
void LL_stack_push(LL_stack *const _stack, int const _data)
{
    add_before(_stack->list,_stack->list->size , _data);
}

 void print_LL_stack(LL_stack const *const _stack ){
    display(_stack->list);
}

void LL_stack_pop(LL_stack *const _stack)
{
    remove_elem(_stack->list, _stack->list->size -1);
}



