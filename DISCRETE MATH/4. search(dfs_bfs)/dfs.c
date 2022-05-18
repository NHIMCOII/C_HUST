#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int vertices;

int visited[MAX];
int pre[MAX], post[MAX];
int clock = 1;

void previsit(int v)
{
    pre[v] = clock;
    clock++;
}

void postvisit(int v)
{
    post[v] = clock;
    clock++;
}

void explore(int v)
{
    visited[v] = 1; // 1: true, 0:false
    previsit(v);

    for (int u = 0; u < vertices; u++)
        if (graph[v][u] == 1)
            if (visited[u] == 0)
                explore(u);
    postvisit(v);
}

void dfs()
{
    for (int v = 0; v < vertices; v++)
        visited[v] = 0;
    for (int v = 0; v < vertices; v++)
        if (visited[v] == 0)
            explore(v);
}

enum edges
{
    forward,
    back,
    cross
};

enum edges categorize(int u, int v)
{
    if (pre[u] < pre[v] && post[u] > post[v])
        return forward;

    if (pre[u] > pre[v] && post[u] < post[v])
        return back;

    return cross;
}

int main(int argc, char const *argv[])
{
    // Open file
    FILE *fptr;
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\8.11.txt", "r");

    if (fptr == NULL)
    {
        printf("Error!"); // Program exits if the file pointer returns NULL.
        exit(1);
    }

    // Initialize graph
    int edges;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            graph[i][j] = 0;

    fscanf(fptr, "%d", &vertices);
    fscanf(fptr, "%d", &edges);

    for (int e = 0; e < edges; e++)
    {
        int u, v;
        fscanf(fptr, "%d%d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    dfs();

    for (int v = 0; v < vertices; v++)
        printf("\n%d:%d-%d", v, pre[v], post[v]);
    printf("\n");
    return 0;
}