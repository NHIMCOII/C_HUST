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
    node_t *travel = head;
    while (travel != NULL)
    {
        printf("%d->", travel->value);
        travel = travel->next;
    }
    printf("\n");
}

void swap_node(node_t **head, node_t* x, node_t* y)
{
    if (x->value == y->value)
        return;

    node_t *prev_X = NULL, *currX = *head;
    while (currX!= NULL && currX->value != x->value)
    {
        prev_X = currX;
        currX = currX->next;
    }

    node_t *prev_Y = NULL, *currY = *head;
    while (currY!= NULL && currY->value != y->value)
    {
        prev_Y = currY;
        currY = currY->next;
    }

    if (currX == NULL || currY == NULL) // can'f find node
        return;

    if (prev_X != NULL)
        prev_X->next = currY;
    else 
        *head = currY;

    if (prev_Y != NULL)
        prev_Y->next = currX;
    else 
        *head = currX;

    node_t *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}


int main()
{
    node_t *head = create_new_node(0);
    node_t *a = create_new_node(2);
    node_t *b = create_new_node(4);
    node_t *c = create_new_node(3);

    head->next = a;
    a->next = b;
    b->next = c;

    print_list(head);
    swap_node(&head,head,c);
    print_list(head);
    printf("%d\n",head->value);
    return 0;
}