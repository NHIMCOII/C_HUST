#include <stdio.h>
int count_blank(char *a)
{
    int count = 0, i = 0;
    while (a[i] != '\0')
    {
        if (a[i] == ' ')
            count++;
        i++;
    }
    return count;
}

int main()
{
    char str[100], c;
    printf("Input string: ");
    fgets(str, 100, stdin);
    printf("Blank space: %d", count_blank(str));
    return 0;
}