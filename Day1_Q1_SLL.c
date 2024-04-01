#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// LinkedList structure
typedef struct LinkedList
{
    Node *head;
    size_t size;
} LinkedList;

// Function to initialize an empty LinkedList
void initLinkedList(LinkedList *const _list)
{
    _list->head = (Node *)malloc(sizeof(Node));
    _list->head->next = (Node *)malloc(sizeof(Node));
    _list->head->next->next = NULL;

    _list->size = 0;
}

// Function to free the memory of the linked list
void destroyLinkedList(LinkedList *const _list)
{
    Node *current = _list->head;
    while (current != NULL)
    {
        Node *toFree = current;
        current = current->next;
        free(toFree);
    }
    _list->head = NULL;
    _list->size = 0;
}

// General function to add a node before any given position
void addAtPosition(LinkedList *const _list, int const _data, size_t const _position)
{
    if (_position < 1 || _position > _list->size + 1)
    {
        printf("\nInvalid position!\n");
        return;
    }

    Node *prev = _list->head;
    for (size_t pos = 1; pos < _position; ++pos)
    {
        prev = prev->next;
    }
    Node *next = prev->next;

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = _data;

    prev->next = newNode;
    newNode->next = next;

    ++_list->size;
}

// Function to add a new node at the beginning of the linked list
void addAtBeginning(LinkedList *const _list, int const _data)
{
    addAtPosition(_list, _data, 1);
}

// Function to add a new node at the end of the linked list
void addAtEnd(LinkedList *const _list, int const _data)
{
    addAtPosition(_list, _data, _list->size + 1);
}

// General Function to delete the node at a specific position in the linked list
void deleteAtPosition(LinkedList *const _list, size_t const _position)
{
    if (_position > _list->size || _position < 1)
    {
        printf("\nInvalid position\n");
        return;
    }

    Node *prev = _list->head;
    for (size_t pos = 1; pos < _position; ++pos)
    {
        prev = prev->next;
    }
    Node *next = prev->next->next;
    free(prev->next);
    prev->next = next;

    --_list->size;
}

// Function to delete the node at the beginning of the linked list
void deleteAtBeginning(LinkedList *const _list)
{
    deleteAtPosition(_list, 1);
}

// Function to delete the node at the end of the linked list
void deleteAtEnd(LinkedList *const _list)
{
    deleteAtPosition(_list, _list->size);
}

// Function to display the linked list
void display(LinkedList const *const _list)
{
    if (_list->size == 0)
        printf("\nList is empty\n");
    else
    {
        printf("\nLinked List(size = %d): ", _list->size);
        Node *temp = _list->head;
        for (unsigned index = 0; index < _list->size; ++index)
        {
            temp = temp->next;
            printf("%d->", temp->data);
        }
        printf("X\n");
    }
}

// Main function
int main()
{
    LinkedList list;
    int i, choice, data, position, testCases;
    initLinkedList(&list);
    do
    {
        printf("\nMenu:\n");
        printf("1. Add at beginning\n");
        printf("2. Add at any position\n");
        printf("3. Add at end\n");
        printf("4. Delete at beginning\n");
        printf("5. Delete at any position\n");
        printf("6. Delete at end\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            addAtBeginning(&list, data);
            display(&list);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &position);
            addAtPosition(&list, data, position);
            display(&list);
            break;
        case 3:
            printf("Enter data: ");
            scanf("%d", &data);
            addAtEnd(&list, data);
            display(&list);
            break;
        case 4:
            deleteAtBeginning(&list);
            display(&list);
            break;
        case 5:
            printf("Enter position: ");
            scanf("%d", &position);
            deleteAtPosition(&list, position);
            display(&list);
            break;
        case 6:
            deleteAtEnd(&list);
            display(&list);
            break;
        case 0:
            printf("\nExiting program.\n");
            destroyLinkedList(&list);
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}
