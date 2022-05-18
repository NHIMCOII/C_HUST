#include <stdio.h>

void replace_char(char *a, char *b, char *c)
{
    int i = 0;
    while (a[i] != '\0')
    {
        if (a[i] == *b)
            a[i] = *c;
        i++;
    }
}

int main()
{
    char str[100];
    char b[2], c[2];
    int i = 0;
    printf("Input string: ");
    scanf("%[^\n]%*c",str);
    printf("Enter char1: ");
    scanf(" %c", b);
    printf("Enter char2: ");
    scanf(" %c", c);

    replace_char(str, b, c);

    printf("%s", str);

    return 0;
}