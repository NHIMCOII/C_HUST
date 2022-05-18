#include<stdio.h>

int main(){
    int n,sum;
    printf("Enter n = ");
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    FILE *fo=fopen("out.txt","w");
    for(int i=n-1;i>=0;i--){
        fprintf(fo,"%d ",a[i]);
    }
    fprintf(fo,"%d\n",sum);
    fclose(fo);
    return 0;
}