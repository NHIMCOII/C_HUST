#include <stdio.h>
#include <string.h>

int strend(char *a, char *b)
{
    int i, k, t = 0, x = 0;
    char c[20];
    k = strlen(a) - strlen(b);
    for (i = k ; a[i] != '\0'; i++)
    {
        c[t] = a[i];
        t++;
    }
    c[t + 1] = '\0';
    if (strcmp(b, c) == 0)
    {
        x = 1;
        return x;
    }
    else
        return x;
}

int main()
{
    char a[100], b[100];
    int x;
    printf("Enter string1: ");
    fgets(a, 100, stdin);
    printf("Enter string2: ");
    fgets(b, 100, stdin);
    x = strend(a, b);
    printf("%d\n", x);
    return 0;
}