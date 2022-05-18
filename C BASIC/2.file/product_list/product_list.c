#include<stdio.h>
#include<stdlib.h>
typedef struct 
{
    int ID;
    char ProductName[100];
    double Price;
}product;


int main(){
    product a[100];
    int index=0;
    FILE *fi=fopen("product.txt","r");
    if(fi==NULL){
        perror("Error\n");
        exit(1);
    }
    while(!feof(fi)){
        fscanf(fi,"%d%s%lf",&a[index].ID,&a[index].ProductName,&a[index].Price);
        index++;
    }
    fclose(fi);
    printf("%-3s %-30s %-10s \n","No","Product Name","Price");
    for(int i=0;i<index;i++){
        printf("%-3d %-30s %-10lf\n",a[i].ID,a[i].ProductName,a[i].Price);
    }
    return 0;
}