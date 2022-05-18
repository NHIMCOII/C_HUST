#include <stdio.h>
#include <string.h>
#include <stdio.h>

int MAX(int a,int b){
    if(a>b) return a;
    return b;
}

int f(int n){
    if(n<=1)return 1;
    if(n%3==1)return f(n-1)+2*f(n-2);
    else return f(n-1)+f(n-2);
}

int main(){
    int n=100;
    int s=0;
    int i,j,k=0;
    for(i=n/2;i<=n;i++)
        for(j=2;j<=n;j=j*2){
            k=k+n/2;
            s++;
        }

    printf("%d\n",s);
    return 0;
}