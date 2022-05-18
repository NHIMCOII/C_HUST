#include<stdio.h>
#include<string.h>

int main(){
    char a[100];
    int i=0;
    printf("Enter string: ");
    fgets(a,100,stdin);
    while(a[i]!='\0'){
        if(a[i]==','||a[i]=='.'||a[i]==';'||a[i]==':'||a[i]=='!'||a[i]=='?')
             a[i]=' ';
             i++;
    }
    fputs(a,stdout);
    return 0;
}