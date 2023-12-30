#include <include/doubly_linked_list.h>

int main()
{
    Doubly_Linked_List *list;
    init_list(list);

    for (int data = 0; data < 25; ++data)
    {
        add_before(list, list->size, data);
    }
    // remove_elem(list, 3);
    // remove_elem(list, 3);
    // remove_elem(list, 0);
    display(list);
    printf("\n");
    display_reverse(list);
    return 0;
}