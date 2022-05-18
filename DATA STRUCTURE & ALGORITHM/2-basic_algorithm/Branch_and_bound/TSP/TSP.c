#include <stdio.h>
#include <stdbool.h>

int c[100][100] = {0};
bool marked[100] = {0};
int a[100], //save progress till the end
    x[100]; //update the best path
int f = 0,
    f_min = 9999, //minimum cost
    cmin = 9999;  //minimum edge unmarked

void Relax(int n)
{ //update result
    if (f + c[a[n]][a[1]] < f_min)
    {
        f_min = f + c[a[n]][a[1]];
        for (int i = 1; i <= n; i++)
            x[i] = a[i];
    }
}

void TRY(int k, int n)
{
    for (int v = 1; v <= n; v++)
    {
        if (marked[v] == false)
        {
            marked[v] = true;
            a[k] = v;
            f = f + c[a[k - 1]][a[k]];
            if (k == n)
            {
                Relax(n);
            }
            else
            {
                for (int i = 1; i <= n; i++)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (marked[i] == false || c[i][j] != 0)
                        {
                            if (cmin > c[i][j])
                                cmin = c[i][j];
                        }
                    }
                }
                int g = f + cmin * (n - k + 1);
                if (g < f_min)
                    TRY(k + 1, n);
            }
            marked[v] = false;
            f = f - c[a[k - 1]][a[k]];
        }
    }
}

int main()
{
    FILE *inp = fopen("cities_05.txt", "r"); //cities_15->8'
    int n;
    printf("Enter number of cities: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fscanf(inp, "%d", &c[i][j]);
    fclose(inp);
    // INITIALIZE
    a[1] = 1;
    marked[1] = true;
    TRY(2, n);
    //

    printf("Min cost = %d \n", f_min);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", x[i]);
    }
    printf("1");
    return 0;
}