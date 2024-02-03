#include <LL_based_stack.h>

int main()
{
    LL_stack stack;
    init_LL_stack(&stack);

    for(unsigned i = 0; i<20; ++i)
    LL_stack_push(&stack, i);
    print_LL_stack(&stack);

    for(unsigned i = 0; i<10; ++i)
    LL_stack_pop(&stack);
    print_LL_stack(&stack);


    return 0;
}