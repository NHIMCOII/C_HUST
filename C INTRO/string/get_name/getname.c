#include <stdio.h>
#include <string.h>
char b[100];

char *get_name(char *a)
{
    int i = 0;
    int j;
    while (a[i] != '\0')
    {
        if (a[i] == ' ')
        {
            for (j = 0; j < i; j++)
            {
                b[j] = a[j];
            }
            b[j + 1] = '\0';
            break;
        }
        i++;
    }
    return b;
}

int main()
{
    char a[100];
    printf("Enter your name: ");
    fgets(a, 100, stdin);
    b[0] = *get_name(a);
    fputs(b, stdout);
    return 0;
}