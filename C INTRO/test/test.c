#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
} node_t;

node_t *create_new_node(int value)
{
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

void print_list(node_t *head)
{
    node_t *temporary = head;
    while ((temporary != NULL))
    {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

int main()
{
    node_t *tmp;
    node_t *head = NULL;
    head=create_new_node(0);
    head->next=tmp;
    for (int i = 1; i < 25; i++)
    {
        tmp=create_new_node(i);
        tmp=tmp->next;
    }

    print_list(head);
    return 0;
}