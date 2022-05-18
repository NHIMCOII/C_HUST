#include<stdio.h>
#include<string.h>
void copy(char* a,char* b){
    int i;
    for(i=0;i<(strlen(a)>strlen(b) ? strlen(a):strlen(b));i++){
        a[i]=b[i];
    }   
}

int main(){
    char a[20],b[20];
    int i;
    printf("string a: ");
    fgets(a,20,stdin);
    printf("string b: ");
    fgets(b,20,stdin);

    copy(a,b);
    printf("%s\n",a);
    return 0;
}