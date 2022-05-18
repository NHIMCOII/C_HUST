#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

int GetNth(node_t *head, int index)
{

    node_t *current = head;

    int count = 0;
    while (current != NULL)
    {
        if (count == index)
            return (current->value);
        count++;
        current = current->next;
    }
}

int main()
{
    int i, n, x,k;
    node_t *head = NULL, *tmp;
    printf("n = ");
    scanf("%d", &n);

    printf("Enter head of list(No.0): ");
    scanf("%d", &x);
    head = create_new_node(x);
    tmp = head;
    node_t *travel;
    for (i = 1; i < n; i++)
    {
        printf("Enter No.%d: ", i);
        scanf("%d", &x);
        travel = create_new_node(x);
        tmp->next = travel;
        tmp = tmp->next;
    }
    printf("k = ");
    scanf("%d",&k);
    
    //Print result
    for (i = k; i < n; i++)
    {
        printf("%d ", GetNth(head, i));
    }
    for(i=0;i<k;i++){
        printf("%d ", GetNth(head, i));
    }
    

    return 0;
}


