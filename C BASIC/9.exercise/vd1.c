#include<stdio.h>
#include<stdlib.h>
// #include"cgen.h"



int main(int argc,char* argv[]){
    if(argc!=3){
        printf("Usage: ./prog inptxt 101\n");
        return 0;
    }
    int q;
    sscanf(argv[2],"%d",&q);
    int n,idx=0;
    FILE *inp=fopen(argv[1],"r");  
    fscanf(inp,"%d",&n);
    int *a=malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        fscanf(inp,"%d",&a[i]);
    }
    fclose(inp);

    printf("n=%d\n",n);
    for(int i=0;i<n;i++){
        printf("%d  ",a[i]);
    }
    return 0;
}