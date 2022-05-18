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

void swap_node(node_t **head, node_t *x, node_t *y)
{
    if (x->value == y->value)
        return;

    node_t *prev_X = NULL, *currX = *head;
    while (currX != NULL && currX->value != x->value)
    {
        prev_X = currX;
        currX = currX->next;
    }

    node_t *prev_Y = NULL, *currY = *head;
    while (currY != NULL && currY->value != y->value)
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
void selection_sort(node_t **head)
{
    node_t *traver = NULL;
    node_t *min = NULL;
    node_t *tmp;
    tmp = *head;
    if (tmp->next == NULL || tmp == NULL)
    {
        return;
    }
    else
    {
        traver = *head;
        while (traver->next != NULL)
        {
            tmp = traver->next;
            min = traver;
            while (tmp != NULL)
            {
                if (traver->value > tmp->value)
                {
                    min = tmp;
                }
                tmp = tmp->next;
            }
            if (traver->value > min->value)
                swap_node(&head, traver, min);

            traver = traver->next;
        }
    }
}

int main()
{
    node_t *head = NULL, *tmp;
    int x, i, n;

    printf("n = ");
    scanf("%d", &n);
    printf("Enter head: ");
    scanf("%d", &x);
    head = create_new_node(x);
    tmp = head;
    node_t *traver;
    for (i = 1; i < n; i++)
    {
        printf("Enter No.%d: ", i);
        scanf("%d", &x);
        traver = create_new_node(x);
        tmp->next = traver;
        tmp = tmp->next;
    }
    print_list(head);
    selection_sort(&head);
    print_list(head);
    printf("%d\n", head->value);

    return 0;
}