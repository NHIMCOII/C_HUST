#include <stdio.h>

typedef struct std_id
{
    char id[6];
    char name[31];
    float grade;
    char classement;
} student;

void clear_buffer(){
    int ch;
    while((ch=getchar())!='\n'&&ch!=EOF);
}


void selection_sort(student *a, int n)
{
    int i, j;
    student tmp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i].grade < a[j].grade)
            {
                tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
        }
    }
}

int main()
{

    int i, n;
    student a[100];

    printf("CLASS OF 2021\n");
    do
    {
        printf("Number of students: ");
        scanf("%d", &n);
    } while (n < 0);

    for (i = 0; i < n; i++)
    {
        printf("\nStudent No.%d\n", i + 1);        
        printf("ID: ");
        fflush(stdin); //clear_buffer();
        gets(a[i].id);
        printf("Name: ");
        gets(a[i].name);
        printf("Grade: ");
        scanf("%f", &a[i].grade);
        if (a[i].grade >= 9 && a[i].grade <= 10)
            a[i].classement = 'A';
        else if (a[i].grade >= 8 && a[i].grade < 9)
            a[i].classement = 'B';
        else if (a[i].grade >= 6.5 && a[i].grade < 8)
            a[i].classement = 'C';
        else if (a[i].grade >= 0 && a[i].grade < 6.5)
            a[i].classement = 'D';
        printf("Classenment: %c\n", a[i].classement);
    }

    selection_sort(a, n);
    printf("\n%-30s %-8s %-10s\n", "Name", "Grade", "Classement");
    for (i = 0; i < n; i++)
    {
        printf("%-30s %-8.1f %-10c\n", a[i].name, a[i].grade, a[i].classement);
    }

    return 0;
}
