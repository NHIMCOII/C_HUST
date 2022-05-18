#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"cgen.h"

#define to_int(p) (*((const int*)p))
int cmp_inc_i(const void *a, const void *b){
    return to_int(b) - to_int(a);
}

int main(){
    clock_t start = clock();
    int k,count=0;
    printf("Enter K = ");
    scanf("%d",&k);

    int a[100];
    
    FILE *inp=fopen("inp.txt","r");  
    while(!feof(inp)){
        fscanf(inp,"%d",&a[count]);
        count++;
    }
    fclose(inp);

    qsort(a,count,sizeof(a[0]),cmp_inc_i);
    clock_t end = clock();
    double time_process=(double)(end-start)/CLOCKS_PER_SEC;
    for(int i=0;i<k;i++){
        printf("%d\n",a[i]);
    }
    printf("Time = %ld",time_process);
    return 0;
}