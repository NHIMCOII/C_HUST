#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int name, d, p; //deadline,profit
} work_info;
int n;
int j = 0; //result[]'s index

work_info a[100],
          result[100] = {0};

void sort()
{
    work_info tmp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i].d > a[j].d)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void Greedy()
{
    sort();
    int count = 1;
    int k = 0;
    while (count!=0)
    {
        result[j]=a[k];
        while(a[k].d==count){
            if(result[j].p<a[k].p)
                result[j]=a[k];
            k++;
        }
        count=a[k].d;
        j++;
    }
}

int main()
{
    printf("Enter number of works: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        a[i].name = i + 1;
        printf("Work No.%d: ", a[i].name);
        scanf("%d %d", &a[i].d, &a[i].p);
    }

    Greedy();
    int profit=0;
    printf("\nWork order for maximum profit: ");
    for (int i = 0; i < j; i++)
    {
        printf("-> %d ", result[i].name);
        profit+=result[i].p;
    }
    printf("\nProfit = %d\n",profit);
    return 0;
}