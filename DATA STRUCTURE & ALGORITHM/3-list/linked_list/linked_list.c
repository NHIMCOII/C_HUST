#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next ;
} *node_t;

void printlist(node_t head)
{
    node_t temporary = head;

    while (temporary != NULL)
    {
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

node_t create_new_node(int value)
{
    node_t result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

node_t locate_node(node_t head, int value)
{
    node_t tmp = head;
    while (tmp != NULL)
    {
        if (tmp->value == value)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void insert_node(node_t head,node_t nn){
    if(head==NULL){
        head=nn;
        return ;
    }
    node_t tmp=head;
    while(tmp->next!=NULL){
        tmp=tmp->next;
    }
    tmp->next=nn;
    return;
}

int main(){
    node_t head=NULL;
    node_t tmp=create_new_node(0);
    insert_node(head,tmp);
    for(int i=1;i<25;i++){
        tmp=create_new_node(i);
        insert_node(head,tmp);
    }

    printlist(head);
    return 0;
}