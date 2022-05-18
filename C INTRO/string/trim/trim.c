#include <stdio.h>
#include <string.h>

void trimRight(char *a)
{
    int l;
    l = strlen(a) - 1;
    while (a[l] == ' ')
    {
        l--;
    }
    a[l + 1] = '\0';
}

void trimLeft(char *a)
{
    int j, i = 0;
    while (a[i] == ' ')
    {
        i++;
    }
    j = i;
    i = 0;
    while (a[i] != '\0')
    {
        a[i] = a[j];
        i++;
        j++;
    }
}

void trimMid(char *a)
{
    int i = 0;
    while (1)
    {
        if (a[i] == ' ' && a[i + 1] == ' ')
        {
            int k = i;
            while (a[k] != '\0')
            {
                a[k + 1] = a[k + 2];
                k++;
                i = 0;
            }
        }
        else
        {
            i++;
            if (a[i] == '\0')
                break;
        }
    }
}

int main()
{
    char a[100];

    printf("Enter string: ");
    gets(a);

    trimRight(a);   
    trimLeft(a); 
    trimMid(a);
    fputs(a, stdout);
    printf("\n");

    return 0;
}