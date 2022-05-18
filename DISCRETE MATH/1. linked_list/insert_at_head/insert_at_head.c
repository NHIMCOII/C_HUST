#include <stdlib.h>
#include <stdio.h>

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
    node_t *traver = head;
    while (traver != NULL)
    {
        printf("%d->", traver->value);
        traver = traver->next;
    }
    printf("\n");
}

void insert_at_head(node_t **head, int value)
{
    node_t *new_head;
    new_head = create_new_node(value);
    new_head->next = *head;
    *head = new_head;
}

node_t *find_node(node_t *head, int value)
{
    node_t *traver = head;
    while (traver != NULL)
    {
        if (traver->value == value)
            return traver;   
        traver=traver->next;     
    }
    printf("Cant find you node!\n");
    return NULL;

}

void remove_node(node_t **head, int value)
{
    node_t *node_to_remove, *traver;
    node_to_remove = find_node(*head, value);
    if (node_to_remove == *head)
    {
        *head = node_to_remove->next;
        return;
    }
    else
    {
        traver = *head;
        while (traver != NULL && traver->next != node_to_remove)
        {
            traver = traver->next;
        }
        if (traver == NULL)
            return;
        traver->next = node_to_remove->next;
        node_to_remove->next = NULL;
    }
    return ;
}

void insert_after_node(node_t *node_to_insert_after, node_t *new_node)
{
    new_node->next = node_to_insert_after->next;
    node_to_insert_after->next = new_node;
}

int main()
{
    int i, n, x;
    node_t *head = NULL, *tmp;
    printf("n = ");
    scanf("%d", &n);

    printf("Enter head of list(No.0): ");
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

    printf("Insert after head: ");
    scanf("%d", &x);
    insert_at_head(&head, x);
    print_list(head);

    printf("Find node with value: ");
    scanf("%d", &x);
    tmp=find_node(head,x);
    printf("Found node %d\n", tmp->value);
    
    printf("Insert after node %d: ",tmp->value);
    scanf("%d",&x);
    insert_after_node(tmp,create_new_node(x));
    print_list(head);

    printf("Remove node with value: ");
    scanf("%d", &x);
    remove_node(&head, x);
    print_list(head);

    return 0;
}