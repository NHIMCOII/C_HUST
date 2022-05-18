#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include<stdlib.h>
    
#define STACK_EMPTY INT_MIN

typedef struct node{
    int value;
    struct node* next;
}node_t;

typedef node_t* stack;


bool push(stack* mystack,int value)
{
    //CREATE NEW NODE
    node_t* newnode=malloc(sizeof(node_t));
    if(newnode==NULL) return false;
    //SAVE NEW NODE'S VALUE
    newnode->value=value;
    newnode->next=*mystack;
    *mystack=newnode;
    return true;
}

int pop(stack* mystack)
{
    if (*mystack == NULL)
        return STACK_EMPTY;
        
    int result = (*mystack)->value;
    node_t* tmp=*mystack;
    *mystack=(*mystack)->next;
    free(tmp);
    return result;
}

int main()
{
    stack s1=NULL,s2=NULL,s3=NULL;
    push(&s1,2);
    push(&s2,45);
    push(&s3,65);
    push(&s1,546);
    push(&s1,45);
    push(&s1,67);
    push(&s1,36);
    push(&s1,29);
    int t;
    while ((t = pop(&s1)) != STACK_EMPTY)
    {
        printf("t = %d\n", t);
    }
    return 0;
}