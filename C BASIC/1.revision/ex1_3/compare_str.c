#include <stdio.h>

int cmp(char *a, char *b, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 0;
        }
    return 1;
}

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    char str1[n], str2[n];

    printf("str1 > ");
    scanf(" %[^\n]%*c", str1);

    printf("str2 > ");
    scanf(" %[^\n]%*c", str2);

    printf("%d", cmp(str1, str2, n));
    return 0;
}