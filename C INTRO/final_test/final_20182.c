#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student
{
    char name[30];
    char id[12];
    char Home_town[30];
    float GPA;
} std;

std a[100];
int n = 0;
float avg;
void opt_1()
{
    int num;
    do
    {
        printf("\n\nNhap so luong sinh vien: ");
        scanf("%d", &num);
    } while (num < 1);

    for (int k = n; k < n + num; k++)
    {
        printf("Thong tin sinh vien No.%d:\n", k + 1);
        printf("Ho va ten: ");
        fflush(stdin);
        gets(a[k].name);
        printf("ID: ");
        fflush(stdin);
        gets(a[k].id);
        printf("Home town: ");
        fflush(stdin);
        gets(a[k].Home_town);
        do
        {
            printf("GPA: ");
            scanf("%f", &a[k].GPA);
        } while (a[k].GPA < 0 || a[k].GPA > 4);
        printf("\n");
    }
    n = n + num;
    return;
}

void opt_2()
{
    int i;
    float sum = 0;
    printf("%-3s %-31s %-15s %-31s %-5s\n", "STT", "Ten", "MSSV", "Que Quan", "GPA");
    for (i = 0; i < n; i++)
    {
        printf("%-3d %-31s %-15s %-31s %-5.1f\n", i + 1, a[i].name, a[i].id, a[i].Home_town, a[i].GPA);
        sum = sum + a[i].GPA;
    }
    printf("\n");
    avg = sum / n;
    printf("Diem GPA trung binh tat ca sinh vien: %.1f", avg);
}

void opt_3()
{
    char str[12];

    printf("Nhap MSSV: ");
    fflush(stdin);
    gets(str);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(a[i].id, str) == 0)
        {
            printf("%-3s %-31s %-15s %-31s %-5s\n", "STT", "Ten", "MSSV", "Que Quan", "GPA");
            printf("%3d %-31s %-15s %-31s %-5.1f\n\n", i + 1, a[i].name, a[i].id, a[i].Home_town, a[i].GPA);
            break;
        }
        if (i == n - 1 && strcmp(a[i].id, str) != 0)
            printf("Khong tim thay sinh vien.\n\n");
    }
}

void opt_4()
{
    char str[30];

    printf("Nhap que quan: ");
    fflush(stdin);
    gets(str);
    printf("%-3s %-31s %-15s %-31s %-5s\n", "STT", "Ten", "MSSV", "Que Quan", "GPA");
    for (int i = 0; i < n; i++)
    {
        if (a[i].GPA > avg && strcmp(a[i].Home_town, str) == 0)
        {
            printf("%3d %-31s %-15s %-31s %-5.1f\n", i + 1, a[i].name, a[i].id, a[i].Home_town, a[i].GPA);
        }
        else if (i == n)
        {
            printf("Khong tim thay sinh vien.\n");
            return;
        }
    }
}

void opt_5()
{
    int i, j;
    std tmp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i].GPA < a[j].GPA)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }

    opt_2();
}

int main()
{
    int m;
    do
    {
        printf("\n\nMENU\n");
        printf("1. Nhap thong tin sinh vien.\n");
        printf("2. In thong tin sinh vien.\n");
        printf("3. Tim kiem theo ma so sinh vien.\n");
        printf("4. Tim kiem theo GPA va que quan.\n");
        printf("5. Sap xep.\n");
        printf("6. Thoat.\n\n");
        printf("Lua chon(1-6): ");
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

        case 5:
        {
            opt_5();
        }
        break;

        default:
        {
            break;
        }
        }
    } while (m != 6);
    return 0;
}
