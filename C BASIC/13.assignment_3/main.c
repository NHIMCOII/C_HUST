#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct _info_{
    char product[20];
    char supplier[20];
} *info;
info A;

int cmp_prod(const void *a,const void *b){
    return strcmp(((info)a)->product,((info)b)->product);
}

int cmp_supp(const void *a,const void *b){
    return strcmp(((info)a)->supplier,((info)b)->supplier);
}

int main(int argc,char* argv[]){
    int start,end;
    double time;
    start=clock();
    if(argc >4||argc<3){
        printf("Usage: ./prog f1 c2 input.txt \n");
        return 0;
    }
    int n=0;
    FILE *fi=fopen(argv[argc-1],"r");
    fscanf(fi,"%d",&n);
    A=calloc(n,sizeof(struct _info_));
    for(int i=0;i<n;i++){
        fscanf(fi,"%s%s",A[i].product,A[i].supplier);
    }
    fclose(fi);
   
    if(strcmp(argv[1],"f1")==0){
        for(int i=0;i<n;i++){
            if(strcmp(A[i].supplier,argv[2])==0)
                printf("%s ",A[i].product);
        }
        end=clock();
        time=(double)(end-start)/CLOCKS_PER_SEC;  
        printf("\nProcessed time: %lf\n",time);
    }
    if(strcmp(argv[1],"f2")==0){
        info B=calloc(0,sizeof(struct _info_));
        int idx=0;
        for(int i=0;i<n;i++){
            if(strcmp(A[i].product,argv[2])==0){
                B=realloc(B,(idx+1)*sizeof(struct _info_));
                strcpy(B[idx].supplier,A[i].supplier);
                idx++;
            }
        }     
        qsort(B,idx,sizeof(B[0]),cmp_supp);
        for(int i=0;i<idx;i++)
            printf("%s ",B[i].supplier);
        free(B);
        end=clock();
        time=(double)(end-start)/CLOCKS_PER_SEC;  
        printf("\nProcessed time: %lf\n",time);
    }
    if(strcmp(argv[1],"f3")==0){
        char key[20]=" ",result[20];
        int idx=0,max=0;
        qsort(A,n,sizeof(A[0]),cmp_prod);
        for(int i=0;i<n;i++){
            if(strcmp(key,A[i].product)!=0){
                strcpy(key,A[i].product);
                idx=1;
            }
            else{
                idx++;
                if(strcmp(key,A[i+1].product)!=0&&max<idx){
                    max=idx;
                    strcpy(result,key);
                }
            }
        }
        idx=0;
        while(strcmp(result,A[idx].product)!=0)
            idx++;
        for(int i=idx;strcmp(A[i].product,result)==0;i++){
            printf("%s ",A[i].supplier);
        }
        end=clock();
        time=(double)(end-start)/CLOCKS_PER_SEC;  
        printf("\nProcessed time: %lf\n",time);
    }
    free(A);
    return 0;
}