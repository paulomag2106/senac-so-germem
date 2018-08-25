#include "memory.h"

typedef struct t_node {
    uint32_t data;
    struct t_node* next;
    struct t_node* prev;
} node;

void append(node** head_ref, uint32_t new_data)
{

    node* new_node = (node*)mem_alloc(sizeof(node));

    node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;

    return;
}

void printList(node *list)
{
    node *last;
    printf("\nReading from Head to Tail\n");
    while (list != NULL) {
        printf(" %u ", list->data);
        last = list;
        list = list->next;
    }

    printf("\nReading backwards\n");
    while (last != NULL) {
        printf(" %u ", last->data);
        last = last->prev;
    }

    printf("\n");
}

void freeList(node *list) {
    printf("Freeing List...\n");

    while (list != NULL) {
        node *next = list->next;
        mem_free(list);
        list = next;
    }
}

int main()
{
    clearHeap();

    node* head = NULL;
    append(&head, UINT_MAX);
    // printHeap();

    append(&head, 32);
    // printHeap();

    append(&head, 4);

    // printHeap();

    printf("Created Doubly Linked List is: ");
    printList(head);
    freeList(head);

    // printHeap();

    return 0;
}
