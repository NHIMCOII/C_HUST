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

void printlist(node_t *head)
{
    node_t *temporary = head;

    while (temporary != NULL)
    {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

int main()
{
    node_t *head = NULL;
    node_t *tmp;
    tmp = create_new_node(0);
    head = tmp;
    
    node_t *traver = head;
    for (int i = 1; i < 25; i++)
    {
        tmp=create_new_node(i);
        while (traver->next != NULL)
        {
            traver = traver->next;
        }
        traver->next = tmp;
    }
    printlist(head);
    
    return 0;
}