#include <stdio.h>
#include <ctype.h>
int main(int argc,char *argv[])
{
    FILE *fi = fopen(argv[1], "r");
    FILE *fo = fopen(argv[2], "w");
    if(argc!=3){
        printf("Usage: ./prog input.txt output.txt");
        return 1;
    }
    if (!fi)
    {
        printf("Error1\n");
        return 1;
    }

    if (!fo)
    {
        printf("Error2");
        return 1;
    }

    int c;
    while ((c = fgetc(fi)) != EOF)
    {
        if (isalpha(c))
        {
            fputc(toupper(c), fo);
        }
        else{
            fputc(c,fo);
        }
    }
    fclose(fi);
    fclose(fo);
    return 0;
}