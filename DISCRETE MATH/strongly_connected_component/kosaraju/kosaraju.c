#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define STACK_LENGTH 20
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

typedef struct
{
    int values[STACK_LENGTH];
    int top;
} stack;

bool visited[20];
int graph[20][20], transposed_graph[20][20];
stack stk;

void insert_matrix(int array[20][20], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            array[i][j] = 0;
        }
    }
    return;
}

//STACK PROCEDURE
bool push(stack *mystack, int value)
{
    if (mystack->top >= STACK_LENGTH - 1)
        return false;

    mystack->top++;
    mystack->values[mystack->top] = value;
    return true;
}

int pop(stack *mystack)
{
    if (mystack->top == EMPTY)
        return STACK_EMPTY;

    int result = mystack->values[mystack->top];
    mystack->top--;
    return result;
}
//
//DFS FIRST TIME TO CREATE STACK
void explore(int v, int size)
{
    visited[v] = true;
    for (int u = 0; u < size; u++)
    {
        if (graph[v][u] == 1)
        {
            if (visited[u] == false)
                explore(u, size);
        }
    }
    push(&stk, v);
}

void DFS_1(int size)
{
    //SETUP VISITED[] ALL FALSE;
    int v;
    for (v = 0; v < size; v++)
    {
        visited[v] = false;
    }
    for (v = 0; v < size; v++)
    {
        if (visited[v] == false)
        {
            explore(v, size);
        }
    }
}
//
//DFS SECOND TIME TO GET SCC
void explore2(int v, int size)
{
    printf("%d ", v);
    visited[v] = true;
    for (int u = 0; u < size; u++)
    {
        if (transposed_graph[v][u] == 1)
        {
            if (visited[u] == false)
                explore2(u, size);
        }
    }
}
////TRAVERSAL BY STACK ORDER
void DFS_2(int size){
    //RESET VISITED[] TO FALSE;
   for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }
    int v;
    while ((v = pop(&stk)) != STACK_EMPTY)
    {
        if (visited[v] == false)
        {
            explore2(v, size);
            printf("\n");
        }
        
    } 
}
//

int main()
{
    FILE *fptr;
    int vertices,edges;
    stk.top = EMPTY;

    //READ FILE AND CREATE MATRIX
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\anti_scc.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        return 1;
    }
    //FIND MATRIX SIZE
    
    fscanf(fptr,"%d %d",&vertices,&edges);
    insert_matrix(graph, vertices);
    insert_matrix(transposed_graph, vertices);
    
    //FILLING MATRIX
    while (!feof(fptr))
    {
        int n, m;
        fscanf(fptr, "%d ", &m);
        fscanf(fptr, "%d", &n);
        graph[m][n] = 1;
        transposed_graph[n][m] = 1;
    }
    fclose(fptr);

    printf("Strongly connected component:\n");
    DFS_1(vertices);
    DFS_2(vertices);

    return 0;
}