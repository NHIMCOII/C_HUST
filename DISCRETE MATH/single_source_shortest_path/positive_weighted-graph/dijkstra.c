#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define oo 100000
//GLOBAL VARIABLES
bool visited[20];
int graph[20][20];
int d[20];
int prev[20];
//
//MATRIX PROCEDURE
void insert_matrix(int size)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            graph[i][j] = 0;
        }
    }
    return;
}
//

//VISITED[],PREV[] AND D[] PROCEDURE
void init_array(int max)
{
    for (int i = 1; i <= max; i++)
    {
        visited[i] = false;
        d[i] = oo;
        prev[i] = -1;
    }
}

int min_array(int vertices)
{
    int index;
    int min = oo;
    for (int i = 1; i <= vertices; i++)
    {
        if (visited[i] != true)
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
//

void Relax(int u, int v)
{
    if (d[v] > d[u] + graph[u][v])
    {
        d[v] = d[u] + graph[u][v];
        prev[v] = u;
    }
    // for(int i=1;i<=8;i++){
    //     printf("%d , %d | ",d[i],prev[i]);
    // }
    // printf("\n");
}

void dijkstra(int start, int vertices)
{
    //INITIALIZE
    init_array(vertices);
    d[start] = 0;
    
    //
    for (int v = 1; v <= vertices; v++)
    {
        int u = min_array(vertices);
        visited[u] = true;
        for (int v = 1; v <= vertices; v++)
        {
            if (graph[u][v] != 0 && visited[v] != true)
                Relax(u, v);
        }
    }
}

int main()
{
    FILE *fptr;
    int start;
    //READ FILE AND CREATE MATRIX
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\8.15.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        exit(1);
    }
    //FIND MATRIX SIZE
    int vertices, edges;
    fscanf(fptr, "%d %d", &vertices,&edges);
    
    //
    insert_matrix(vertices);
    //FILLING MATRIX
    while (!feof(fptr))
    {
        int n, m, weight;
        fscanf(fptr, "%d %d %d", &m,&n,&weight);
        graph[m][n] = weight;
    }
    fclose(fptr);
    do
    {
        printf("Enter start(1-%d): ", vertices);
        scanf("%d", &start);
    } while (start < 1 || start > vertices);

    dijkstra(start, vertices);

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