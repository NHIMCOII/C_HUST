#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define to_int(p) (*((const int*)p))
int cmp(const void *a, const void *b){
    return to_int(a) - to_int(b);
}

int binSearch(int l,int r,int *a,int q){
    if(l>=r)
        return 0;
    int i=(l+r)/2;
    if(a[i]>q){
        return binSearch(l,i,a,q);
    }
    else if(a[i]<q){
        return binSearch(i+1,r,a,q);
    }
    return 1;
}

int Solution(int *a,int n,int q){
    int count=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]+a[j]==q)
                count++;
        }
    }
    return count;
}

int main(int argc,char* argv[]){
    if(argc!=3){
        printf("Usage: ./prog inptxt 101\n");
        return 0;
    }
    int q;
    sscanf(argv[2],"%d",&q);
    int n,idx=0;
    FILE *inp=fopen(argv[1],"r");  
    fscanf(inp,"%d",&n);
    int *a=malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        fscanf(inp,"%d",&a[i]);
    }
    fclose(inp);
    
    int start1,end1,start2,end2;
    double time1,time2;

    // printf("\nTim kiem nhi phan: %d\n",binSearch(0,n,a,2));
// VET CAN
    start1=clock();
    printf("\nVet can: %d\n",Solution(a,n,q));
    end1=clock();
    time1=(double)(end1-start1)/CLOCKS_PER_SEC;
    printf("Time_1: %lf \n\n",time1);
// 
// TKNP
    start2=clock();
    qsort(a,n,sizeof(a[0]),cmp);
    int count=0;
    for(int i=0;i<n-1;i++){
        if(binSearch(i+1,n,a,(q-a[i]))==1)
            count++;
    }
    end2=clock();
    time2=(double)(end2-start2)/CLOCKS_PER_SEC;
// 
    printf("Giai quyet bang tknp: %d\n",count);
    printf("Time_2: %lf\n\n",time2);

    printf("Time1/Time2 = %lf\n",time1/time2);
    free(a);
    return 0;
}