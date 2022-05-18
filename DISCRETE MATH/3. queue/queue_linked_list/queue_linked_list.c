#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#define QUEUE_EMPTY INT_MIN

typedef struct node
{
    int value;
    struct node *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
} queue;

void init_queue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(queue *q, int value)
{
    //CREATE A NEW NODE
    node_t *newnode = malloc(sizeof(node_t));
    if (newnode == NULL)
        return false;
    newnode->value = value;
    newnode->next = NULL;
    //IF THERE IS A TAIL, CONNECT THAT TAIL TO THIS NEW NODE
    if (q->tail != NULL)
    {
        q->tail->next = newnode;
    }
    q->tail = newnode;
    //MAKE SURE THE HEAD STILL MAKE SENSE
    if (q->head == NULL)
    {
        q->head = newnode;
    }
    return true;
}
int dequeue(queue *q)
{
    //CHECK IF THE QUEUE IS EMPTY
    if(q->head==NULL)return QUEUE_EMPTY;
    //SAVE THE HEAD OF THE QUEUE
    node_t* tmp= q->head;
    //SAVE THE RESULT
    int result=tmp->value;
    //TAKE IT OFF
    q->head=q->head->next;
    if(q->head==NULL){
        q->tail=NULL;
    }
    free(tmp);
    return result;
}

int main()
{
    queue q1 , q2 , q3 ;
    
    init_queue(&q1);
    init_queue(&q2);
    init_queue(&q3);
    
    enqueue(&q1, 2);
    enqueue(&q2, 45);
    enqueue(&q3, 65);
    enqueue(&q1, 546);
    enqueue(&q1, 45);
    enqueue(&q1, 67);
    enqueue(&q1, 36);
    enqueue(&q1, 29);
    int t;
    while ((t = dequeue(&q1)) != QUEUE_EMPTY)
    {
        printf("t = %d\n", t);
    }
    return 0;
}