#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define to_str(p) (*((const char*)p))
int cmp_inc_s(const void *a, const void *b){
    to_str(a); 
    to_str(b);
    // printf("%s %s\n",b,a);
    return strcmp(a,b);
}

int main(){
    int n;
    char **a;
    printf("Enter n = ");
    scanf("%d",&n);
    a=malloc(n*sizeof(char*));
    printf("> ");
    for(int i=0;i<n;i++){
        a[i]=malloc(sizeof(char));
        scanf("%s",&a[i]);
    }

    printf("\nBefore sort: ");
    for(int i=0;i<n;i++){
        printf("[%s]  ",&a[i]);
    }

    qsort(a,n,sizeof(a[0]),cmp_inc_s);
    printf("\nAfter sort: ");
    for(int i=0;i<n;i++){
        printf("[%s]  ",&a[i]);
    }

    free(a);
    return 0;
}