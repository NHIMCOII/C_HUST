#include<stdio.h>
int c=1;
int add(int a,int b){
    int s=0;
    if(c==2)
        return b;
    c++;
    s=add(0,b)+a;
    return s;
}
int main(){
    int s=add(5,15);
    printf("%d\n",s);
    return 0;
}