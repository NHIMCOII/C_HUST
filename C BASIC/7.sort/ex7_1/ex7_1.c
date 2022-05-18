#include<stdio.h>
#include<stdlib.h>

#define to_int(p) (*((const int*)p))
int cmp_inc_i(const void *a, const void *b){
    return to_int(a) - to_int(b);
}

int main(){
    int n;
    printf("Enter n = ");
    scanf("%d",&n);
    float *a=malloc(n*sizeof(float));
    printf("> ");
    for(int i=0;i<n;i++){
        scanf("%f",&a[i]);
    }

    qsort(a,n,sizeof(a[0]),cmp_inc_i);

    for(int i=0;i<n;i++){
        printf("%.2f  ",a[i]);
    }

    free(a);
    return 0;
}