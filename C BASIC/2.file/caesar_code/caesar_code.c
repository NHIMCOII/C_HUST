#include<stdio.h>

int main(){
    int n;
    printf("Enter offset(n) = ");
    scanf("%d",&n);
    
    FILE *fi=fopen("input.txt","r");
    FILE *fo=fopen("output.txt","w");
    if(!fi){
        printf("Error1!\n");
        return 1;
    }
    if(!fo){
        printf("Error2!\n");
        return 1;
    }
    int c;
    while((c=fgetc(fi))!=EOF){
        fputc(c+n,fo);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}