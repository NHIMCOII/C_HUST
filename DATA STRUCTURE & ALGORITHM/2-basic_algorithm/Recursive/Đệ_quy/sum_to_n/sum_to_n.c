#include<stdio.h>
// 1 + 2 + 3 + 4 +...+ n 
int sum(int n){
    if(n<=1)
        return 1;
    int s=sum(n-1);
    return s+n;
}

int main(){
    int n;
    printf("\nEnter n = ");
    scanf("%d",&n);
    printf("Sum = %d\n\n",sum(n));
    return 0;
}