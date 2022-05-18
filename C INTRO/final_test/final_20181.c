#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void opt_1()
{
    int a[10][10], b[10][10];
    int n, count = 0;
    do
    {
        printf("n = ");
        scanf("%d", &n);
    } while (n < 2);
    printf("Nhap ma tran: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    //INSERT MA TRAN DON VI
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                b[i][j] = 1;
            else
                b[i][j] = 0;
        }
    }
    //
    //SO SANH MA TRAN NHAP VA MA TRAN DON VI
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == b[i][j])
            {
                count++;
                if (count == n * n)
                {
                    printf("Co\n");
                    return;
                }
            }
            else
            {
                printf("Khong\n");
                return;
            }
        }
    }
    //
}

void opt_2()
{
    int  space, rows, k;
    char ch;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter option (X,N): ");
    fflush(stdin);
    scanf("%c", &ch);

    switch (ch)
    {
    case 88:
    case 120:
    {
        for (int i = 1; i <= rows; i++)
        {
            for (space = 1; space <= rows - i; space++)
            {
                printf("  ");
            }
            for (k = 0; k != 2 * i - 1; k++)
            {
                printf("* ");
            }
            printf("\n");
        }
    }
    break;

    case 78:
    case 110:
    {
        int i,j;
        for (i = rows; i >= 1; i--)
        {
            for (space = 0; space < rows - i; space++)
                printf("  ");
            for (j = i; j <= 2 * i - 1; j++)
                printf("* ");
            for (j = 0; j < i - 1; j++)
                printf("* ");
            printf("\n");
        }
    }

    default:
        break;
    }
}

void opt_3()
{
    unsigned long long int pnum;
    char str[20];
    printf("DOI SO DIEN THOAI:\n");
    scanf("%llu", &pnum);
    sprintf(str, "%llu", pnum);            //CONVERT LONGLONGINT TO STRING
    str[11] = '\0';                        //CUT
    unsigned long long int x = atoll(str); //CONVERT STRING TO LONGLONGINT

    if (strlen(str) == 10)
    {
        printf("%llu\n", x);
        return;
    }
    if (x >= 16200000000 && x <= 16999999999)
    {
        x = x - 13000000000;
        printf("%llu\n", x);
        return;
    }
    else
        printf("Khac nha mang!\n");
}

void opt_4()
{
    typedef struct
    {
        int phan_nguyen;
        int tu_so;
        int mau_so;
    } hon_so;
    hon_so h1, h2, result;

    char cross;
    printf("Nhap 2 hon so:\n");
    scanf("%d %d %c %d", &h1.phan_nguyen, &h1.tu_so, &cross, &h1.mau_so);
    scanf("%d %d %c %d", &h2.phan_nguyen, &h2.tu_so, &cross, &h2.mau_so);
    h1.tu_so = h1.phan_nguyen * h1.mau_so + h1.tu_so;
    h2.tu_so = h2.phan_nguyen * h2.mau_so + h2.tu_so;
    result.tu_so = h1.tu_so * h2.mau_so;
    result.mau_so = h2.tu_so * h1.mau_so;
    result.phan_nguyen = result.tu_so / result.mau_so;
    result.tu_so = result.tu_so - result.phan_nguyen * result.mau_so;
    //UCLN
    int a = result.tu_so;
    int b = result.mau_so;
    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    //
    result.tu_so=result.tu_so/a;
    result.mau_so=result.mau_so/a;
    printf("%d %d/%d\n", result.phan_nguyen, result.tu_so, result.mau_so);
}

int main()
{
    int m;
    do
    {
        printf("\n\nMENU\n");
        printf(" 1. Ma tran\n");
        printf(" 2. Tam giac\n");
        printf(" 3. Chuyen so\n");
        printf(" 4. Phan so\n");
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
            opt_4();
        }
        break;

        default:
            break;
        }
    } while (m != 5);
    return 0;
}