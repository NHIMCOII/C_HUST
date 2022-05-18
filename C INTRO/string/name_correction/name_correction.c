#include <stdio.h>
#include <string.h>
#include <ctype.h>
void trim(char *a)
{
    int i;
    for (i = 0; i < strlen(a); i++)
    {
        if (a[i] == ' ' && a[i + 1] == ' ')
        {
            strcpy(a + i, a + i + 1);
            i--;
        }
        if (a[0] == ' ')
            strcpy(a, a + 1);

        if (a[strlen(a) - 1] == ' ')
            a[strlen(a) - 1] = '\0';
    }
}

void name_correction(char *a)
{
    int i = 0;
    trim(a);
    while (a[i] != '\0')
    {
        a[0] = toupper(a[0]);
        if ((a[i] >= 'a' && a[i] <= 'z') && (a[i - 1] == ' '))
        {
            a[i] = a[i] - 32;
        }
        if ((a[i] >= 'A' && a[i] <= 'Z') && (a[i - 1] != ' '))
        {
            a[i] = a[i] + 32;
        }
        if(a[i] == '.'&&a[i+1]=='\0'){
            a[i-1]='.';
            a[i]='\0';
        }
        i++;
    }
}

int main()
{
    char a[100];

    printf("Enter string: ");
    gets(a);
    name_correction(a);
    fputs(a, stdout);
    printf("\n");

    return 0;
}