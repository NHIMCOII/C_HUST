#include<stdio.h>

int fibonacci(int n){
    if(n<=1) return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}

int main(){
    int n,fibo[100]={0};
    printf("Enter n = ");
    scanf("%d",&n);
    fibo[0]=1;fibo[1]=1;
        for(int i=2;i<=n;i++){
        fibo[i]=fibo[i-1]+fibo[i-2];
    }
    printf("%d\n",fibo[n]);
    // printf("%d\n",fibonacci(n));
    return 0;
}