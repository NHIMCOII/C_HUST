#include<stdio.h>

// tim kiem trg khoang nua mo l<=i<r
// tra ve 1 neu tim thay q, tra ve 0 neu ngc lai

int binsearch(int l,int r,int *a,int q){
    if(l>=r)
        return 0;
    int i=(l+r)/2;
    if(a[i]>q){
        return binsearch(l,i,a,q);
    }
    else if(a[i]<q){
        return binsearch(i+1,r,a,q);
    }
    return 1;
}

int main(){
    int a[]={10,20,30,50,60,70,80,90,100,110,120};
    int n=sizeof(a)/sizeof(a[0]);
    printf("%d\n",binsearch(0,n,a,130));
    return 0;

}