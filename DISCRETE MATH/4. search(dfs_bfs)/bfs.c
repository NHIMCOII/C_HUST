#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define oo 10000 // Vô cùng
#define EMPTY -1
#define QUEUE_EMPTY INT_MIN

int dist[MAX];
int prev[MAX]; //prev[u] = v  <-> đỉnh trước của đỉnh u trong đường đi là v
int n = 100;
int G[MAX][MAX] = {
   //S  A  B  C  D  E
    {0, 1, 0, 1, 1, 1}, //S
    {1, 0, 1, 0, 0, 0}, //A
    {0, 1, 0, 1, 0, 0}, //B
    {1, 0, 1, 0, 0, 0}, //C
    {1, 0, 0, 0, 0, 1}, //D
    {1, 0, 0, 0, 1, 0}  //E
};

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct
{
    node *head;
    node *tail;
} queue;

void init_queue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(queue *q, int value)
{
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
        return false;

    newnode->value = value;
    newnode->next = NULL;

    if (q->tail != NULL)
        q->tail->next = newnode;

    q->tail = newnode;

    if (q->head == NULL)
        q->head = newnode;

    return true;
}

int dequeue(queue *q)
{
    if (q->head == NULL)
        return QUEUE_EMPTY;

    node *tmp = q->head;
    int result = tmp->value;

    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;

    free(tmp);
    return result;
}

bool is_empty(queue *q)
{
    if (q->head == NULL)
        return true;
    return false;
}

void print_queue(queue *q)
{
    int t;
    while ((t = dequeue(q)) != QUEUE_EMPTY)
    {
        printf("T = %d\n", t);
    }
}

void bfs(int s)
{
    queue q1;
    init_queue(&q1);

    for (int u = 0; u < n; u++)
        dist[u] = oo;

    prev[s] = -1; // Đỉnh s không có đỉnh trước vì bắt đầu từ s
    dist[s] = 0;
    enqueue(&q1, s); // Q.push(s);

    while (is_empty(&q1) != true)
    {
        int u = dequeue(&q1); // int u = Q.front();
        // Q.pop(); // loại bỏ u khỏi hàng đợi
        for (int v = 0; v < n; v++)
            if (G[u][v] == 1) // Có cạnh (u,v) trong E
            {
                if (dist[v] == oo)
                {
                    enqueue(&q1, v); //Q.push(v);    // đưa v vào hàng đợi
                    prev[v] = u;     // đỉnh trước của đỉnh v là đỉnh u
                    dist[v] = dist[u] + 1;
                }
            }
    }
}

// Tìm đường ngắn nhất từ s tới u
void findPath(int s, int u)
{
    bfs(s);
    while (u != s)
    {
        printf("%i <- ", u); //cout << u << "<-";
        u = prev[u];
    }
    printf("%i", s); // cout << s << endl;
}

int main(int argc, char const *argv[])
{
    findPath(0, 2);

    return 0;
}
