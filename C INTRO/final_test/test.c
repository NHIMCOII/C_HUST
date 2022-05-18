#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int ID;
    char Nation[3];
    float R[3];
    char Name[30];
    float Result;
} vdv;

vdv a[20];
int num;
void opt_1()
{
    do
    {
        printf("Nhap so luong van dong vien: ");
        scanf("%d", &num);
    } while (num < 1 || num > 20);
    for (int i = 0; i < num; i++)
    {
        printf("Van dong vien No.%d: \n", i + 1);
        printf("ID: ");
        scanf("%d", &a[i].ID);

        printf("Nation: ");
        fflush(stdin);
        gets(a[i].Nation);

        printf("Name: ");
        fflush(stdin);
        gets(a[i].Name);
    }
}

void opt_2()
{
    printf("%-5s %-10s %-20s %-5s %-5s %-5s %-5s\n", "ID", "Nation", "Name", "R1", "R2", "R3", "FR");
    for (int i = 0; i < num; i++)
    {
        printf("%-5d %-10s %-20s %-5.2f %-5.2f %-5.2f %-5.2f\n", a[i].ID, a[i].Nation, a[i].Name, a[i].R[0], a[i].R[1], a[i].R[2], a[i].Result);
    }
}

void opt_3()
{
    float FR = 0;
    for (int i = 0; i < 3; i++)
    {
        printf("Luot thi R%d: \n", i + 1);
        for (int j = 0; j < num; j++)
        {
            printf("R%d - ID:%d > ", i + 1, a[j].ID);
            scanf("%f", &a[j].R[i]);
        }
        opt_2();
    }
    printf("\n");
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i].R[j] > FR)
                FR = a[i].R[j];
        }
        a[i].Result = FR;
        FR = 0;
    }
    opt_2();
}

void opt_4()
{
    char str[30];
    printf("Tim kiem theo quoc gia: ");
    fflush(stdin);
    gets(str);
    printf("%-5s %-10s %-20s %-5s %-5s %-5s %-5s\n", "ID", "Nation", "Name", "R1", "R2", "R3", "FR");
    for (int i = 0; i < num; i++)
    {
        if (strcmp(a[i].Nation, str) == 0)
        {
            printf("%-5d %-10s %-20s %-5.2f %-5.2f %-5.2f %-5.2f\n", a[i].ID, a[i].Nation, a[i].Name, a[i].R[0], a[i].R[1], a[i].R[2], a[i].Result);
        }
    }

    printf("Tim kiem theo ten vdv: ");
    fflush(stdin);
    gets(str);
    for (int i = 0; i < num; i++)
    {
        if (strcmp(a[i].Name, str) == 0)
        {
            printf("%-5d %-10s %-20s %-5.2f %-5.2f %-5.2f %-5.2f\n", a[i].ID, a[i].Nation, a[i].Name, a[i].R[0], a[i].R[1], a[i].R[2], a[i].Result);
        }
    }
}

void opt_5(){
    int i, j;
    vdv tmp;
    for (i = 0; i < num - 1; i++)
    {
        for (j = i + 1; j < num; j++)
        {
            if (a[i].Result < a[j].Result)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }

    opt_2();
}

void main()
{
    opt_1();
    opt_2();
    opt_3();
    opt_4();
    opt_5();
    return;
}