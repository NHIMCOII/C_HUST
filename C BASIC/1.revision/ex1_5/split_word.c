#include<stdio.h>
#include<ctype.h>
int main(){
    char *ptr[100];
    int i=0;
    char str[100]={'\0'};
    int count=0;
    printf("> ");
    scanf(" %[^\n]%*c",str);
    ptr[0]=&str[0];
    int k=1;
    while(str[i]!='\0'){
        if(!isalpha(str[i])){
            str[i]='\0';
            if(isalpha(str[i+1])){
                ptr[k]=&str[i+1];
                count++;
                k++;
            }
        }
        i++;
    }

    for(int i=count;i>=0;i--){
        puts(ptr[i]);
    }
    return 0;
}