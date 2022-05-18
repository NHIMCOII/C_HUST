// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<time.h>
// #include "ext\io.h"
// #define N 12

// int n_order,n_product;

// typedef struct _prod_{
//     char *product;
//     int price;
// }prod;

// typedef struct _order_{
//     char *id;
//     int total;
// }order;

// int cmp_func(const void *a,const void *b){
//     return strcmp(((prod*)a)->product,((prod*)b)->product);
// }

// int cmp_func2(const void *a,const void *b){
//     return ((order *)b)->total - ((order *)a)->total;
// }

// void update(char *key,int m,prod *P,order *O,int idx){
//     prod *result;
//     printf("ye\n");
//     result=bsearch(key,P,n_product,sizeof(P[0]),cmp_func);
//     O[idx].total += m * result->price;
// }

// int main(int argc, char *argv[]){
//     int start,end;
//     double time;
//     start=clock();
//     if (argc != 3)
//     {
//         printf("Usage: ./prog products.txt orders.txt \n");
//         return 0;
//     }
// //------------------------------------------------------------------
//     FILE *f_prod = fopen(argv[1],"r");
//     fscanf(f_prod, "%d\n", &n_product);
//     prod P[n_product-1];
//     char *line=NULL;
//     int idx=0;
//     while (cgetline(&line, 0, f_prod))
//     {
//         if(line[strlen(line)-1]=='\n')
//             line[strlen(line)-1]='\0';
//         token = strtok(line," ");
//         P[idx].product=strdup(token);
//         token = strtok(NULL," ");
//         P[idx].price=atoi(token);
//         idx++;
//     }
//     fclose(f_prod);
//     qsort(P,n_product,sizeof(P[0]),cmp_func);
// //------------------------------------------------------------------
//     FILE *f_ord = fopen(argv[2], "r");
//     fscanf(f_ord, "%d\n", &n_order);
//     order O[n_order];
//     line=NULL;
//     idx=0;
//     while (cgetline(&line, 0, f_prod))
//     {
//         O[idx].total=0;
//         int nb;
//         if(line[strlen(line)-1]=='\n')
//             line[strlen(line)-1]='\0';
//         char *token= strtok(line," ");
//         while(token!=NULL){
//             O[idx].id=token;           
//             token=strtok(NULL," ");
//             nb=atoi(token);
//             token=strtok(NULL," ");
//             for(int i=0;i<nb;i++){
//                 char *key;
//                 key=token;
//                 token=strtok(NULL," ");  
//                 // update(key,atoi(token),P,O,idx);
//                 token=strtok(NULL," "); 
//             }
//         }
//         idx++;
//     }
//     fclose(f_ord);
//     // qsort(O,n_order,sizeof(O[0]),cmp_func2);
// //------------------------------------------------------------------
//     // for(int i=0;i<3;i++){
//     //     printf("%s %d \n",O[i].id,O[i].total);
//     // }
//     // free(array);
//     end=clock();
//     time=(double)(end-start)/CLOCKS_PER_SEC;
//     printf("Processed time: %lf \n",time);
//     return 0;
// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ext/io.h"
#include "cgen.h"
#include <time.h>



typedef struct Order{
    char code[20];
    int total;
}Order;

typedef struct Product{
    char code[20];
    char price[100];
}Product;

Product binsearch(Product * a,char * foo, int l,int r){
    if(r>=l){
        int m = l + (r - l) / 2;
        if(strcmp(a[m].code,foo) == 0){
            return a[m];
        }
        else if(strcmp(a[m].code,foo) > 0){
            return binsearch(a,foo,l,m-1);
        }
        else{
            return binsearch(a,foo,m+1,r);
        }
    }
}

int cmpfunc(const void * a, const void * b){
    const int  ia = ((const Order *)a)->total;
    const int  ib = ((const Order *)b)->total;
    return ib - ia;
}

int cmpfuncCode(const void * a, const void * b){
    const char * ia = ((const Product *)a)->code;
    const char * ib = ((const Product *)b)->code;
    return strcmp(ia, ib);
}

int main(int argc, char * argv[]){
    clock_t begin = clock();
    if(argc != 3){
        printf("wrong!");
        return -1;
    }
    FILE * product_file = fopen(argv[1], "r");
    FILE * order_file = fopen(argv[2], "r");
    int n,m;
    char * line1 = NULL; // very important to set to NULL
    cgetline(&line1,0,product_file);
    n = atoi(line1);
    cgetline(&line1,0,order_file);
    m = atoi(line1);
    if(m<=3){
        printf("too low");
        return 0;
    }
    Product * list_p = (struct Product *)malloc(sizeof(struct Product)*n);
    int counter =0;
    while(cgetline(&line1,0,product_file)){
        if (line1[strlen(line1) - 1] == '\n') {
                line1[strlen(line1) - 1] = '\0';
            }
            char * tok = strtok(line1, " ");
            strcpy(list_p[counter].code, tok);
            tok = strtok(NULL, " ");
            strcpy(list_p[counter].price, tok);
            counter++;
    }
    qsort(list_p,n,sizeof(struct Product), cmpfuncCode);
    /*for(int i =0;i<n;i++){
        printf("%s %s\n",list_p[i].code,list_p[i].price);
    }*/
    counter = 0;
    Order * list_o = (struct Order *)malloc(sizeof(struct Order)*m);
    while(cgetline(&line1,0,order_file)){
        if (line1[strlen(line1) - 1] == '\n') {
                line1[strlen(line1) - 1] = '\0';
            }
            char * tok = strtok(line1, " ");
            strcpy(list_o[counter].code, tok);
            tok = strtok(NULL, " ");
            int amount = atoi(tok);
            list_o[counter].total = 0;
            if(amount <=0){
                printf("invalid amount");
                continue;
            }
            for(int i =0;i<amount;i++){
                tok = strtok(NULL, " ");
                char * key = strdup(tok);
                tok = strtok(NULL, " ");
                int number = atoi(tok);
                Product found = binsearch(list_p,key,0,n-1);
                list_o[counter].total += atoi(found.price)*number;
                /*for(int j= 0;j<n;j++){
                    if(strcmp(key,list_p[j].code) == 0){
                        list_o[counter].total += atoi(list_p[j].price)*number;
                    }
                }*/
                free(key);
            }
            counter++;
    }
    qsort(list_o,m,sizeof(struct Order), cmpfunc);
    for(int i =0;i<3;i++){
        printf("%s %d\n",list_o[i].code,list_o[i].total);
    }
    fclose(product_file);
    fclose(order_file);
    free(list_p);
    free(list_o);
    free(line1);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    return 0;
}