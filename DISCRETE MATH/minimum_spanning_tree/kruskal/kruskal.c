#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct
{
    int head;
    int tail;
    int weight;
} edge;

//GLOBAL VARIABLES
int count_MST_edges = 0;
int d[20];
int prev[20];
int graph[20][20];
edge e[20];
//

//MATRIX PROCEDURE
void init_matrix(int matrix[20][20], int vertices)
{
    for (int i = 1; i <= vertices; i++)
    {
        for (int j = 1; j <= vertices; j++)
        {
            matrix[i][j] = 0;
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
        d[i] = 0;
        prev[i] = -1;
    }
    return;
}
//

//EDGES PROCEDURE
int edge_list(int vertices)
{
    int i = 1;
    for (int u = 1; u <= vertices; u++)
    {
        for (int v = 1; v <= vertices; v++)
        {
            if (graph[u][v] != 0)
            {
                e[i].head = u;
                e[i].tail = v;
                e[i].weight = graph[u][v];
                i++;
            }
        }
    }
}

void sort_edges(int edges)
{
    edge tmp;
    for (int i = 1; i < edges; i++)
    {
        for (int j = i + 1; j <= edges; j++)
        {
            if (e[i].weight > e[j].weight)
            {
                tmp = e[i];
                e[i] = e[j];
                e[j] = tmp;
            }
        }
    }
}
//

//DISJOINT SET UNION PROCEDURE
int find(int head)
{
    if (prev[head] == -1)
        return head;
    return find(prev[head]);
}

void UNION(int head, int tail)
{
    prev[tail] = head;
}
//

bool detect_cycle(edge a, int vertices)
{
    
        int i = find(a.head); //FIND ABSOLUTE ROOT
        int j = find(a.tail);
        if (i == j)
            return true;
        UNION(a.head, a.tail);
    
    return false;
}

void kruskal(int vertices, int edges)
{
    init_array(vertices);

    for (int k = 1; k <= edges; k++)
    {
        if (detect_cycle(e[k], vertices) == false)
        {
            d[e[k].tail] = e[k].weight;
            count_MST_edges++;
            if (count_MST_edges == (vertices - 1))
                return;
        }
    }
}

int main()
{
    FILE *fptr;
    fptr = fopen("C:\\Users\\PC\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\DISCRETE MATH\\graph\\dijkstra_graph.txt", "r");
    if (fptr == NULL)
    {
        perror("Error\n");
        exit(1);
    }

    int vertices, edges;
    fscanf(fptr, "%d %d", &vertices, &edges);

    init_matrix(graph, vertices);

    while (!feof(fptr))
    {
        int m, n, weight;
        fscanf(fptr, "%d %d %d", &m, &n, &weight);
        graph[m][n] = weight;
    }
    fclose(fptr);

    edge_list(vertices);
    sort_edges(edges);
    kruskal(vertices, edges);

    //PRINT RESULT MST
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
