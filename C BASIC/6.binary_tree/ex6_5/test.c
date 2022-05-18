#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *inp=fopen("story.txt","r");
    char* str;
    while(!feof(inp)){
        fscanf(inp,"%s",str);
        printf("%s\n",str);
    }
    fclose(inp);
    return 0;
}