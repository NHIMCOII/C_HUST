#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cauhoi
{
    int nhom;
    char noidung[255];
    char dapan[5][255];
} cauhoi;

cauhoi list[500];

void nhapdapan(FILE *fp, int index, cauhoi list[500], int count)
{
    fscanf(fp, "  %[^\n]s", list[index].dapan[count]);
    count++;
    char ch;
    fscanf(fp, "\n%c", &ch);
    if (ch == '#')
        return nhapdapan(fp, index, list, count);
}

int main()
{
    FILE *fp = fopen("cauhoi.txt", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    char ch;
    int index = 0;
    fscanf(fp, "%c%c", &ch, &ch);
    while (ch == '*')
    {
        fscanf(fp, "%i", &list[index].nhom);
        fscanf(fp, " %[^\n]s", list[index].noidung);
        fscanf(fp, "\n%c", &ch);
        int count = 0;
        if (ch == '#')
            nhapdapan(fp, index, list, 0);
        fscanf(fp, "%c", &ch);
        index++;
    }
    printf("%i\n", list[0].nhom);
    printf("%s\n", list[0].noidung);
    printf("%s", list[0].dapan[0]);
}