#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 20

int n_order,n_product;

typedef struct _prod_{
    char product[N];
    int price;
}prod;
prod *P;

typedef struct _order_{
    char id[N];
    int total;
}order;
order *O;

int cmp_func(const void *a,const void *b){
    return strcmp(((prod*)a)->product,((prod*)b)->product);
}

int cmp_func2(const void *a,const void *b){
    return ((order *)b)->total - ((order *)a)->total;
}

void update(char *key,int m,int idx){
    prod *result;
    result=bsearch(key,P,n_product,sizeof(P[0]),cmp_func);
    O[idx].total += m * result->price;
}

int main(int argc, char *argv[]){
    int start,end;
    double time;
    start=clock();
    if (argc != 3)
    {
        printf("Usage: ./prog products.txt orders.txt \n");
        return 0;
    }
//------------------------------------------------------------------
    FILE *f_prod = fopen(argv[1],"r");
    fscanf(f_prod, "%d", &n_product);
    P=calloc(n_product,sizeof(prod));
    for(int i=0;i<n_product;i++)
        fscanf(f_prod,"%s%d",P[i].product,&P[i].price);
    fclose(f_prod);
    qsort(P,n_product,sizeof(P[0]),cmp_func);
//------------------------------------------------------------------
    FILE *f_ord = fopen(argv[2], "r");
    fscanf(f_ord, "%d", &n_order);
    O=calloc(n_order,sizeof(prod));
    for(int k=0;k<n_order;k++){
        int nb;
        O[k].total=0;       
        fscanf(f_ord,"%s%d",O[k].id,&nb);
        for(int i=0;i<nb;i++){
            char key[N];
            int m;
            fscanf(f_ord,"%s%d",key,&m);
            update(key,m,k);
        }
    }
    fclose(f_ord);
    qsort(O,n_order,sizeof(O[0]),cmp_func2);
//------------------------------------------------------------------
    for(int i=0;i<3;i++){
        printf("%-15s %15d \n",O[i].id,O[i].total);
    }

    free(O);
    free(P);
    end=clock();
    time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Processed time: %lf \n",time);
    return 0;
}