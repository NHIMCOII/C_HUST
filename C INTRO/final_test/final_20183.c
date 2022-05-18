#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void opt_1()
{
    int n;
    do
    {
        scanf("%d", &n);
    } while (n > 20 || n < 0);
    int a[n], xhien[100];

    for (int i = 0; i < 100; i++)
    {
        xhien[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        xhien[a[i]]++;
    }
    printf("\n");
    for (int i = 0; i < 100; i++)
    {
        if (xhien[i] != 0)
            printf("%d %d\n", i, xhien[i]);
    }
}

void opt_2()
{
    int n;
    do
    {
        scanf("%d", &n);
    } while (n > 30 || n < 1);
    int fibo[31];
    fibo[1] = 0;
    fibo[2] = 1;
    for (int i = 3; i <= 30; i++)
    {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }
    printf("%d\n", fibo[n]);
}

void opt_3()
{
    char str[30];
    int check = 0;
    fflush(stdin);
    gets(str);

    if (strlen(str) < 10)
    {
        printf("False\n");
        return;
    }
    else
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] >= 48 && str[i] <= 57)
            {
                check++;
                break;
            }
        }
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] >= 65 && str[i] <= 90)
            {
                check++;
                break;
            }
        }
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] >= 97 && str[i] <= 122)
            {
                check++;
                break;
            }
        }
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] < 48 || (str[i] > 57 && str[i] < 65) || (str[i] > 90 && str[i] < 97) || str[i] > 122)
            {
                printf("False\n");
                return;
            }
        }
        if (check == 3)
        {
            printf("True\n");
            return;
        }
    }
}

int main()
{
    int m;
    do
    {
        printf("\n\nMENU\n");
        printf(" 1. Frequency\n");
        printf(" 2. Fibonacci\n");
        printf(" 3. Password\n");
        printf(" 4. Date\n");
        printf(" 5. Exit\n");
        printf("Press (1,2,3,4,5) to choose: ");
        scanf("%d", &m);

        switch (m)
        {
        case 1:
        {
            opt_1();
        }
        break;

        case 2:
        {
            opt_2();
        }
        break;

        case 3:
        {
           opt_3();
        }
        break;

        case 4:
        {
            
        }
        break;

        default:
            break;
        }
    } while (m != 5);
    return 0;
}