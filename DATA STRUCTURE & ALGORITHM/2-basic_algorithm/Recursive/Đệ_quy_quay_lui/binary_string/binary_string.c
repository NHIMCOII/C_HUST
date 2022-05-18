#include <stdio.h>
int x[100];
int n;
void solution()
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d", x[i]);
    }
    printf("\n");
}
// modify check() to fit demand(no combination with 2bit 1 next to each other)
int check(int v, int k)
{
    if (x[k - 1] + v ==0 )
        return 0;
    else
        return 1;
}

void Try(int k)
{
    for (int v = 0; v <= 1; v++)
    {
        if (check(v, k))
        {
            x[k] = v;
            if (k == n )
                solution();
            else
                Try(k + 1);
        }
    }
}

int main()
{   x[0]=0;
    printf("Enter number of bits n = ");
    scanf("%d", &n);
    Try(0);
    return 0;
}