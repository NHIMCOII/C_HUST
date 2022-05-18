#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#define QUEUE_EMPTY INT_MIN

typedef struct node
{
    char name;//s->a->...->t
    int value;//weight
    int num;//NUMBERING
    int index;
    struct node *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
} queue;

//GLOBAL VARIABLES
queue q;
int in_node[20]; //number of vector point to a vertex
//

//LINKED LIST PROCEDURE
node_t *create_new_node(char name)
{
    node_t *result = malloc(sizeof(node_t));
    result->name = name;
    result->next = NULL;
    result->value = 0;
    result->index = -1;
    return result;
}

void print_list(node_t *head)
{
    node_t *traver = head;
    while (traver != NULL)
    {
        printf("%c->", traver->name);
        traver = traver->next;
    }
    printf("\n");
}
//

//QUEUE PROCEDURE
void init_queue()
{
    q.head = NULL;
    q.tail = NULL;
}

bool enqueue(int value)
{
    //CREATE A NEW NODE
    node_t *newnode = malloc(sizeof(node_t));
    if (newnode == NULL)
        return false;
    newnode->index = value;
    newnode->next = NULL;
    //IF THERE IS A TAIL, CONNECT THAT TAIL TO THIS NEW NODE
    if (q.tail != NULL)
    {
        q.tail->next = newnode;
    }
    q.tail = newnode;
    //MAKE SURE THE HEAD STILL MAKE SENSE
    if (q.head == NULL)
    {
        q.head = newnode;
    }
    return true;
}

int dequeue()
{
    //CHECK IF THE QUEUE IS EMPTY
    if (q.head == NULL)
        return QUEUE_EMPTY;
    //SAVE THE HEAD OF THE QUEUE
    node_t *tmp = q.head;
    //SAVE THE RESULT
    int result = tmp->index;
    //TAKE IT OFF
    q.head = q.head->next;
    if (q.head == NULL)
    {
        q.tail = NULL;
    }
    free(tmp);
    return result;
}
//
//SET INDEX IN EACH LINKED LIST
void set_index(int vertices, node_t *A[vertices])
{

    for (int i = 0; i < vertices; i++)
    {
        int index = A[i]->index;
        for (int j = 0; j < vertices; j++)
        {
            node_t *traver = A[j]->next;
            while (traver != NULL)
            {
                if (traver->name == A[i]->name)
                    traver->index = index;
                traver = traver->next;
            }
        }
    }
}
//
//CHECK QUEUE
void check_q(){
    
    while(q.head!=NULL){
        int u=dequeue();
        printf("%d ",u);
    }printf("\n");
}
//

int main()
{
    FILE *fptr;
    int vertices, edges;

    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\numbering_graph2.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        exit(1);
    }
    //FIND MATRIX SIZE
    fscanf(fptr, "%d %d %d", &vertices, &edges);
    //
    //INITIAL
    int w;
    char m, n, k = 97;
    node_t *A[vertices];
    A[0] = create_new_node('s');
    A[vertices - 1] = create_new_node('t');
    for (int i = 1; i < vertices - 1; i++)
    {
        A[i] = create_new_node(k);//k=a->....
        k++;
    }
    for (int i = 0; i < vertices; i++)
    {
        A[i]->index = i;
    }
    //
    for (int i = 0; i < vertices; i++)
    {
        node_t *head = A[i];
        node_t *tmp = head, *traver;
        while (!feof(fptr))
        {
            fscanf(fptr, "%c %c %d ", &m, &n, &w);

            if (A[i]->name == m)
            {
                traver = create_new_node(n);
                traver->value = w;
                tmp->next = traver;
                tmp = tmp->next;
            }
            if (A[i]->name == n)
            { //SET UP IN_NODE
                in_node[i]++;
            }
        }
        rewind(fptr);
        fscanf(fptr, "%d %d %d", &vertices, &edges);
    }
    fclose(fptr);

    for (int i = 0; i < vertices; i++)
    {
        print_list(A[i]);
    }
    //NUMBERING
    
    init_queue();
    set_index(vertices, A);
    for (int v = 0; v < vertices; v++)
    {
        if (in_node[v] == 0)
        {
            enqueue(v);
        }
    }
    
    int nr = -1;

    while (q.head != NULL)
    {
        int u = dequeue();
        nr++;
        A[u]->num = nr ;
        node_t *traver = A[u]->next;
        while (traver != NULL)
        {
            in_node[traver->index]--;
            if (in_node[traver->index] == 0)
                enqueue(traver->index);
            traver = traver->next;
        }        
    }
    //
    printf("NUMBERING:\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%c ", A[i]->name);
    }printf("\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%d ", A[i]->num);
    }
}