#include<stdio.h>

int a[1000]={0};
int n=0;

void insert(int x,int p){
    if(p>n)
        insert(x,n);
    for(int j=n-1;j>=p;j--)
        a[j+1]=a[j];
    a[p]=x;
    n++;
    a[n]=-1;
}

void delete(int p){
    for(int j=p+1;j<=n-1;j++)
        a[j-1]=a[j];
    n=n-1;
}

int retrieve(int p){
    return a[p];
}

int locate(int x){
    for(int j=0;j<=n-1;j++)
        if(a[j]==x) return j;
    return -1;
}

void makeNull(){
    n=0;
}

int next(int p){
    if(0<=p&&p<n-1)
        return p+1;
    return -1;
}

int prev(int p){
    if(p>0&&p<=n-1)
        return p-1;
    return -1;
}

int main(){ 
    insert(-1,0);
    for(int i=1;i<100;i++){
        insert(i,i);
    }
    delete(4);
    printf("%d\n",a[100]);
    printf("%d\n",a[4]);
    printf("%d\n",n);

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int a[100000];
int n;

void insert(int x, int p)
{
    for (int j = n - 1; j >= p; j--)
    {
        a[j + 1] = a[j];
    }
    a[p] = x;
    n = n + 1;
}

void del(int p)
{
    for (int j = p + 1; j < n - 1; j++)
    {
        a[j - 1] = a[j];
    }
    n = n - 1;
}

int locate(int x)
{
    for (int j = 0; j <= n - 1; j++)
        if (a[j] == x)
            return j;
    return -1;
}

int main()
{
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        insert(rand() % 100, i);
    }
    for (int i = 0; i < 50; i++)
    {
        del(rand() % 50);
    }
    for (int i = 0; i < 50; i++)
    {
        printf("%d ", a[i]);
    }
}*/