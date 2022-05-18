#include <stdio.h>
#include <string.h>

int main()
{
    char a[5][30] = {"TV126  31 inch Television",
                     "CD057  CD Player",
                     "TA877  Answering Machine",
                     "CS409  Car Stereo",
                     "PC655  Personal Computer"};
    char *ptr;
    char str[100];
    printf("\nEnter item's code: ");
    gets(str);

    for (int i = 0; i < 5; i++)
    {
        ptr = strstr(a[i], str);
        if (ptr != NULL)
        {
            printf("%s\n\n", ptr);
            break;
        }
        else if (i == 4)
            printf("Can't find your item\n\n");
    }
    return 0;
}