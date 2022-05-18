#include <stdio.h>

int main()
{
    char str[100];
    int k = 0, dem = 0;
    printf("(ID:abc1234)\n");
    printf("> ");
    scanf("%s", str);
    while (str[k] != '\0')
    {

        if (k >= 0 && k <= 2)
        {
            if ((str[k] >= 'A' && str[k] <= 'Z') || (str[k] >= 'a' && str[k] <= 'z'))
            {
                dem++;
            }
        }
        if (k >= 3 && k <= 6)
        {
            if (str[k] >= '0' && str[k] <= '9')
            {
                dem++;
            }
        }
        k++;
    }
    
    if (dem == 7)
    {
        printf("Valid");
    }
    else
    {
        printf("Invalid");
    }
    return 0;
}
