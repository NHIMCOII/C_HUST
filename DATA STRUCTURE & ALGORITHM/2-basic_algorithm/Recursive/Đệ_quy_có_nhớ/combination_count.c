#include<stdio.h>
#define MAX 100

/*LONGER TIME TO CALCULATE
int C(int k,int n){
    if(k==0||k==n){
        return 1;
    }
    int C1=C(k-1,n-1);
    int C2=C(k,n-1);
    return C1+C2;
}*/

int m[MAX][MAX];
int C(int k,int n){
    if(k==0||k==n){
        m[k][n]=1;
    }
    else{
        if(m[k][n]<0){
            m[k][n]=C(k-1,n-1)+C(k,n-1);
        }
    }
    return m[k][n];
}

int main(){
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            m[i][j]=-1;
        }
    }
    int k,n;
    printf("Enter k,n : ");
    scanf("%d%d",&k,&n);
    printf("%d\n",C(k,n));
    return 0;
}