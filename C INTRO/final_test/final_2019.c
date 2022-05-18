#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char TenSV[20];
    float DiemQT,DiemCK,DiemTK;
    char DiemXL;
} DiemSV;

int n;
DiemSV a[41];

void opt_1()
{
    do
    {
        printf("Nhap so sinh vien: ");
        scanf("%d", &n);
        if (n <= 0 || n > 40)
            printf("So sinh vien phai nam trong [1,40]\n");
    } while (n <= 0 || n > 40);
    for (int i = 0; i < n; i++)
    {
        printf("Nhap thong tin sinh vien No.%d:\n", i + 1);
        printf("Ten SV: ");
        fflush(stdin);
        gets(a[i].TenSV);
        do
        {
            printf("Diem QT: ");
            scanf("%f",&a[i].DiemQT );
        } while (a[i].DiemQT<0 ||a[i].DiemQT> 10);
        do
        {
            printf("Diem CK: ");
            scanf("%f",&a[i].DiemCK );
        } while (a[i].DiemCK<0 ||a[i].DiemCK> 10);
        a[i].DiemTK=0.4*a[i].DiemQT+0.6*a[i].DiemCK;
        if(a[i].DiemQT<=3||a[i].DiemCK<=3){
            a[i].DiemXL='F';
        }
        else{
            if(a[i].DiemTK<4) a[i].DiemXL='F';
            if(a[i].DiemTK>=4&&a[i].DiemTK<5.5) a[i].DiemXL='D';
            if(a[i].DiemTK>=5.5&&a[i].DiemTK<7) a[i].DiemXL='C';
            if(a[i].DiemTK>=7&&a[i].DiemTK<8.5) a[i].DiemXL='B';
            if(a[i].DiemTK>=8.5&&a[i].DiemTK<=10) a[i].DiemXL='A';
        }
    }
    return;
}

void opt_2()
{
    if (n == 0)
    {
        printf("\nChua co du lieu sinh vien\n");
    }
    else
    {
        printf("%-20s %-10s %-10s %-10s %-10s\n", "Ten SV", "Diem QT", "Diem CK", "Diem TK", "Xep Loai");
        for (int i = 0; i < n; i++)
        {
            printf("%-20s %-10.1f %-10.1f %-10.1f %-10c\n", a[i].TenSV, a[i].DiemQT, a[i].DiemCK, a[i].DiemTK, a[i].DiemXL);
        }
    }
    return;
}

void opt_3()
{
    int count = 0;
    float l;
    do
    {
        printf("Nhap so diem: ");
        scanf("%f", &l);
    } while (l < 2 || l > 5);
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Ten SV", "Diem QT", "Diem CK", "Diem TK", "Xep Loai");
    for (int i = 0; i < n; i++)
    {
        if ((a[i].DiemQT - a[i].DiemCK) >= l)
        {
            printf("%-20s %-10.1f %-10.1f %-10.1f %-10c\n", a[i].TenSV, a[i].DiemQT, a[i].DiemCK, a[i].DiemTK, a[i].DiemXL);
            count++;
        }
        if (i == n && count == 0)
        {
            printf("Khong tin thay sinh vien theo yeu cau.");
        }
    }
    return;
}

void opt_4()
{
    int i, j;
    DiemSV tmp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i].DiemTK < a[j].DiemTK)
            {
                tmp = a[i];
                a[i]= a[j];
                a[j]=tmp;
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
        printf("\n\nChuong Trinh Quan Ly Diem Mon Hoc\n");
        printf(" 1. Nhap diem\n");
        printf(" 2. In bang diem\n");
        printf(" 3. Chenh lech diem\n");
        printf(" 4. Sap xep\n");
        printf(" 5. Thoat chuong trinh\n\n");
        printf(" Press (1,2,3,4,5) to choose: ");
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
        {
            break;
        }
        }
    } while (m != 5);
    return 0;
}