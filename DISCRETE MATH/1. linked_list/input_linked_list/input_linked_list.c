#include<stdio.h>
#include<stdlib.h>

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



int main(){
    int i, n, x;
    node_t *head = NULL, *tmp;
    printf("n = ");
    scanf("%d", &n);
    
    printf("Enter head of list(No.0): ");
    scanf("%d",&x);
    head=create_new_node(x);
    tmp=head;
    node_t* travel;
    for (i = 1; i < n; i++)
    {
        printf("Enter No.%d: ",i);
        scanf("%d",&x);
        travel=create_new_node(x);
        tmp->next=travel;
        tmp=tmp->next;
    }

    printlist(head);

    return 0;
}