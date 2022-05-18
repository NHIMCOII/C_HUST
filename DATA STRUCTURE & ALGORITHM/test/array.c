#include <stdio.h>
#include <stdlib.h>
int n,a[100]={0};

int MAX(int a,int b){
    if(a>b) return a;
    return b;
}


int main(){
    printf("Enter n: ");
    scanf("%d",&n);
    printf("Enter array:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }


    return 0;
}