#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define oo INT_MAX

//GLOBAL VARIABLES
bool MST_SET[20];
int d[20];
int prev[20];
int graph[20][20];
//
//MATRIX PROCEDURE
void init_matrix(int vertices)
{
    for (int i = 1; i <= vertices; i++)
    {
        for (int j = 1; j <= vertices; j++)
        {
            graph[i][j] = 0;
        }
    }
    return;
}

//
//ARRAY PROCEDURE
void init_array(int vertices)
{
    for (int i = 1; i <= vertices; i++)
    {
        MST_SET[i] = false;
        d[i] = oo;
        prev[i] = -1;
    }
    return;
}
//
int min_in_d(int vertices)
{
    int index;
    int min = oo;
    for (int i = 1; i <= vertices; i++)
    {
        if (MST_SET[i] != true)
        {
            if (min > d[i])
            {
                min = d[i];
                index = i;
            }
        }
    }
    return index;
}

void incident_vertex(int u, int vertices)
{
    for (int v = 1; v <= vertices; v++)
    {
        if (graph[u][v] != 0 && d[v] > graph[u][v] && MST_SET[v] != true)
        {
            d[v] = graph[u][v];
            prev[v] = u;
        }
    }
}
//

void prim(int min_vertex, int vertices)
{
    init_array(vertices);
    d[min_vertex] = 0;
    for (int i = 1; i <= (vertices - 1); i++)
    {
        int u = min_in_d(vertices);
        MST_SET[u] = true;
        incident_vertex(u, vertices);
    }
}
int main()
{

    FILE *fptr;
    int min_edge = oo, min_vertex;
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\prim_vs_dijkstra_graph.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        exit(1);
    }
    int vertices, edges;
    fscanf(fptr, "%d %d", &vertices, &edges);

    init_matrix(vertices);

    while (!feof(fptr))
    {
        int m, n, weight;
        fscanf(fptr, "%d %d %d", &m, &n, &weight);
        if (min_edge > weight)
        {
            min_edge = weight;
            min_vertex = m;
        }
        graph[m][n] = weight;
    }
    fclose(fptr);
    prim(min_vertex, vertices);

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
