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

//GLOBAL VARIABLES
queue q;
int prev[100];
//

//LINKED LIST PROCEDURE
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
//

//QUEUE PROCEDURE
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
    if (q->head == NULL)
        return QUEUE_EMPTY;
    //SAVE THE HEAD OF THE QUEUE
    node_t *tmp = q->head;
    //SAVE THE RESULT
    int result = tmp->value;
    //TAKE IT OFF
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    free(tmp);
    return result;
}
//

void BFS(int size, node_t *A[size], int start,int dest)
{
    init_queue(&q);
    bool visited[size];
    for (int i = 0; i <= size; i++)
        visited[i] = false;

    node_t *temp;
    temp = A[start];
    visited[start] = true;
    prev[start]=-1;
    enqueue(&q, temp->value);
    while (q.head != NULL)
    {
        int u = dequeue(&q);
        
        temp = A[u];
        while (temp != NULL)
        {
            if (visited[temp->value] == false)
            {
                enqueue(&q, temp->value);
                visited[temp->value] = true;
                prev[temp->value]=u;                             
            }
            temp = temp->next;
        }
    }
}

void find_path(int size, node_t *A[size], int start, int dest)
{
    BFS(size, A, start,dest);
    while(dest!=start){
        printf("%d <- ",dest);
        dest=prev[dest];
    }
    printf("%d",start);
}

int main()
{
    FILE *fptr;
    int max = 0, num;
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DATA STRUCTURE\\graph\\undirected.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        exit(1);
    }
    //FIND MATRIX SIZE
    while (!feof(fptr))
    {
        fscanf(fptr, "%d ", &num);
        if (max < num)
            max = num;
    }
    rewind(fptr);
    //
    int m, n;

    node_t *A[max];
    for (int i = 0; i <= max; i++)
    {
        A[i] = create_new_node(i);
    }
    for (int i = 0; i <= max; i++)
    {
        node_t *head = A[i];
        node_t *tmp = head, *traver;
        while (!feof(fptr))
        {
            fscanf(fptr, "%d ", &m);
            fscanf(fptr, "%d\n", &n);
            if (m == i)
            {
                traver = create_new_node(n);
                tmp->next = traver;
                tmp = tmp->next;
            }
            if (n == i)
            {
                traver = create_new_node(m);
                tmp->next = traver;
                tmp = tmp->next;
            }
        }
        rewind(fptr);
    }
    fclose(fptr);
    for (int i = 0; i <= max; i++)
    {
        print_list(A[i]);
    }
    int start, dest;
    printf("Start(0-%d): ", max);
    scanf("%d", &start);
    printf("Destination(0-%d): ", max);
    scanf("%d", &dest);
    BFS(max,A,start,dest);
    
    find_path(max,A,start,dest);
    return 0;
}