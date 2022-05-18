#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define oo 10000
//GLOBAL VARIABLES
int graph[20][20];
int d[20];
int prev[20];
int count = 0;
//
//MATRIX PROCEDURE
void insert_matrix(int array[20][20], int size)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 0; j <= size; j++)
        {
            array[i][j] = 0;
        }
    }
    return;
}
//

void Relax(int u, int v)
{
    if (d[v] > d[u] + graph[u][v])
    {
        d[v] = d[u] + graph[u][v];
        prev[v] = u;
        count++; //TO BREAK THE LOOP
    }
}

void bellman_ford(int start, int vertices)
{
    //INITIALIZE
    for (int v = 1; v <= vertices; v++)
    {
        d[v] = oo;
        prev[v] = -1;
    }
    d[start] = 0;

    //
    for (int k = 1; k <= vertices; k++)
    {
        for (int u = 1; u <= vertices; u++)
        {
            for (int v = 1; v <= vertices; v++)
            {
                if (graph[u][v] != 0)
                {
                    Relax(u, v);
                }
            }
        }
        if (count == 0) //BREAK IF NO D[U] UPDATED IN V LOOP;
            return;
        count = 0;
    }
}

int main()
{
    FILE *fptr;
    int start;
    //READ FILE AND CREATE MATRIX
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\bellman_ford_graph.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        exit(1);
    }
    //FIND MATRIX SIZE
    int vertices, edges;
    fscanf(fptr, "%d", &vertices);
    fscanf(fptr, "%d", &edges);
    //
    insert_matrix(graph, vertices);
    //FILLING MATRIX
    while (!feof(fptr))
    {
        int n, m, weight;
        fscanf(fptr, "%d", &m);
        fscanf(fptr, "%d", &n);
        fscanf(fptr, "%d", &weight);
        graph[m][n] = weight;
    }
    fclose(fptr);
    do
    {
        printf("Enter start(1-%d): ", vertices);
        scanf("%d", &start);
    } while (start < 1 || start > vertices);

    bellman_ford(start, vertices);

    //PRINT RESULT
    printf("%18s", "VERTICES:");
    for (int v = 1; v <= vertices; v++)
    {
        printf("%3d ", v);
    }
    printf("\n");
    printf("%18s", "PREVIOUS VERTEX:");
    for (int i = 1; i <= vertices; i++)
    {
        printf("%3d ", prev[i]); //PREVIOUS VERTEX
    }
    printf("\n");
    printf("%18s", "SHORTEST DISTANCE:");
    for (int i = 1; i <= vertices; i++)
    {
        printf("%3d ", d[i]); //DISTANCE
    }
    printf("\n");

    return 0;
}