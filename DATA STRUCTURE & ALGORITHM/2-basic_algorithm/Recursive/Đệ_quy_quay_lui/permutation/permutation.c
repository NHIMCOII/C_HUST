#include <stdio.h>

int n;
int m[100] = {0};
int x[100];

void printSolution()
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void TRY(int i)
{
    for (int v = 1; v <= n; v++)
    {
        if (!m[v])
        {
            x[i] = v;
            m[v] = 1;
            if (i == n)
                printSolution();
            else
                TRY(i + 1);
            m[v] = 0;
        }
    }
}

int main()
{
    printf("Enter n = ");
    scanf("%d", &n);
    TRY(1);
    return 0;
}