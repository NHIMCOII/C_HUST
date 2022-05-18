#include <stdio.h>

typedef struct fraction
{
    int numerator, denominator;
    float value;
} frac;

void input_frac(frac *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Frac No.%d\n", i + 1);
        printf("Numerator = ");
        scanf("%d", &a[i].numerator);
        do
        {
            printf("Denominator = ");
            scanf("%d", &a[i].denominator);
        } while (a[i].denominator == 0);
    }
}

void print_frac(frac *a, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Frac No.%d: %d/%d\n", i + 1, a[i].numerator, a[i].denominator);
    }
}

void Inversion(frac *a, int n)
{
    int i, tmp;
    for (i = 0; i < n; i++)
    {
        tmp = a[i].denominator;
        a[i].denominator = a[i].numerator;
        a[i].numerator = tmp;
    }
}

int frac_cmp(frac *a)
{
    int i;
    a[0].value = a[0].numerator / a[0].denominator;
    a[1].value = a[1].numerator / a[1].denominator;
    if (a[0].value > a[1].value)
        return 1;
    else if (a[0].value == a[1].value)
        return 0;
    else if (a[0].value < a[1].value)
        return -1;
}

int main()
{
    frac a[10];
    int i, n, x;
    do
    {
        printf("Number of fractions: ");
        scanf("%d", &n);
    } while (n < 1);

    input_frac(a, n);

    Inversion(a, n);

    print_frac(a, n);

    if (n == 2)
    {
        x = frac_cmp(a);
        switch (x)
        {
        case 1:
            printf("%d/%d > %d/%d\n", a[0].numerator, a[0].denominator, a[1].numerator, a[1].denominator);
            break;
        case 0:
            printf("%d/%d = %d/%d\n", a[0].numerator, a[0].denominator, a[1].numerator, a[1].denominator);
            break;
        case -1:
            printf("%d/%d < %d/%d\n", a[0].numerator, a[0].denominator, a[1].numerator, a[1].denominator);
            break;

        default:
            break;
        }
    }
    return 0;
}
