#include<stdio.h>
#include<math.h>

#define N 10
int main(){
    double a[N];
    double sum,avg;
    printf("Enter %d numbers: ",N);
    for(int i=0; i<N; ++i){
        scanf("%lf",&a[i]);
        sum+=a[i];
    }
    avg=sum/N;
    double min=a[0];
    for(int i=0;i<N;i++){
        if(fabs(avg-a[i])<min)
            min=fabs(avg-a[i]);
    }

    for(int i=0 ;i<N;i++){
        if(fabs(avg-a[i])==min){
            printf("%.0lf a[%d]\n",a[i],i);
        }
    }
    return 0;
}