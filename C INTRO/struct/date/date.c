#include <stdio.h>

typedef struct _date_
{
    int day;
    int month;
    int year;
} date;

void input(date *a)
{
    do
    {
        printf("day: ");
        scanf("%d", &a->day);
    } while (a->day < 1 || a->day > 31);
    do
    {
        printf("month: ");
        scanf("%d", &a->month);
    } while (a->month < 1 || a->month > 12);
    printf("year: ");
    scanf("%d", &a->year);
}

int datecmp(date d1, date d2)
{
    int x;
    if (d1.year < d2.year)
        x = -1;
    else if (d1.year > d2.year)
        x = 1;
    else if (d1.year == d2.year)
    {
        if (d1.month < d2.month)
            x = -1;
        else if (d1.month > d2.month)
            x = 1;
        else if (d1.month == d2.month)
        {
            if (d1.day < d2.day)
                x = -1;
            else if (d1.day > d2.day)
                x = 1;
            else if (d1.day == d2.day)
                x = 0;
        }
    }
    return x;
}

int main()
{
    date d1, d2;
    int x;
    printf("DATE 01\n");
    input(&d1);
    printf("\n");
    printf("DATE 02\n");
    input(&d2);
    x = datecmp(d1, d2);
    switch (x)
    {
    case -1:
        printf("date1->date2\n");
        break;
    case 0:
        printf("date1=date2\n");
        break;
    case 1:
        printf("date2->date1\n");
        break;

    default:
        break;
    }
    return 0;
}