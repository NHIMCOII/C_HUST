#include<stdio.h>

int x[100]={1,2,3,4,5,6,7,8,9};

int bSearch(int *x,int start,int finish,int y){
    if(start==finish){
        if(x[start==y])
        return start;
        else return -1;
    }else{
        int m=(start + finish)/2;
        if(x[m]==y)return m;
        if(x[m]<y)
        return bSearch(x,m+1,finish,y);
        else
        return bSearch(x,start,m-1,y);
    }
}

int main(){
    printf("%d\n",bSearch(x,3,8,7));
    return 0;
}