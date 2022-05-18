#include<stdio.h>
#include<string.h>
int main(){
    FILE *fi=fopen("count_line.c","r");
    FILE *fo=fopen("output.txt","w");
    int count=1;
    if(!fi){
        printf("Error1\n");
        return 1;
    }

    if(!fo){
        printf("Error2");
        return 1;
    }

    char c[100];
    while((fgets(c,100,fi))!=NULL){
        fprintf(fo,"%d - %s",count,c);
        if(strstr(c,"\n")){
            count++;
        }
    }
    fprintf(fo,"\nLine = %d",count);
    fclose(fi);
    fclose(fo);
    return 0;
}