#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int head;
    int tail;
} set;

int n;
int count=0;
set a[100],
    result[100] = {0};
bool marked[100] = {0};

void sort()
{
    set tmp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (a[i].tail > a[j].tail)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
    }
}

bool isEmpty()
{
    for (int i = 0; i < n; i++)
    {
        if (marked[i] == false)
            return false;
        return true;
    }
}

bool feasible(set ab)
{
    for (int i = 0; i < n; i++)
    {
        if ((ab.head > result[i].tail) || (ab.tail < result[i].head))
            return true;
        return false;
    }
}

void Greedy()
{
    sort();
    while (isEmpty() == false)
    {
        for (int i = 0; i < n; i++)
        {
            marked[i] = true;
            if(feasible(a[i])){
                result[count]=a[i];
                count++;
            }
        }
    }
}

int main()
{
    printf("Enter number of subset: ");
    scanf("%d", &n);
    printf("Input subset (ai,bi) with ai<bi:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].head, &a[i].tail);
    }

    Greedy();
    printf("Result: \n");
    for (int i = 0; i < count; i++)
    {
        printf("%d %d\n",result[i].head,result[i].tail);
    }

    return 0;
}