#include <stdio.h>
#include <ctype.h>

int main()
{
    int count[256] = {0};
    char c;

    printf("Enter string: ");
    while (c = getchar())
    {
        if (c == '\n')
            break;
        if(isalpha(c))
            count[c]++;
    }

    for(int i=0;i<256;i++){
        if(count[i]>0){
            printf("%c - %d\n",i,count[i]);
        }
    }
    return 0;
}