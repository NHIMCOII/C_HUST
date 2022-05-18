#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"
#define N 10
rbm_t t;

void f1(int argc,char *file){
    FILE *fi=fopen(file,"r");
    if(argc!=2){
        printf("Usage: ./prog BongDa.txt\n");
        exit(1);
    }
    t=rbm_create(gtype_cmp_s,gtype_free_s,NULL);
    char fc1[N],fc2[N];
    int sc1=0,sc2=0;
    while(!feof(fi)){
        fscanf(fi,"%s%s%d%d",fc1,fc2,&sc1,&sc2);
        int a=0,b=0;
        if(sc1>sc2){
            a=3;b=0;
        }
        else if(sc1==sc2){
            a=1;b=1;
        }
        else{
            a=0;b=3;
        }

        char *str1=strdup(fc1);
        char *str2=strdup(fc2);
        rbm_ires tmp1 = rbm_insert(t,gtype_s(str1),gtype_l(a));       
        rbm_ires tmp2 = rbm_insert(t,gtype_s(str2),gtype_l(b));

        if(!tmp1.inserted){
            tmp1.value->l+=a;
            free(str1);
        }
        else 
            printf("%s %p\n",str1,tmp1);
        
        if(!tmp2.inserted){
            tmp2.value->l+=b;
            free(str2);
        }
        else    
            printf("%s %p\n",str2,tmp2);
    }
    fclose(fi);
    printf("Luu thong tin thanh cong!\n");
}

void f2(rbm_t t){
    printf("\nKet qua: \n");
    rbm_traverse(k,v,t){
        printf("%s %ld\n",k->s,v->l);
    }
}

void f3(){
    char key[10];
    printf("Nhap ten doi bong: ");
    scanf(" %[^\n]%*c",key);
    gtype* tmp=rbm_value(t,gtype_s(key));
    if(tmp){
        printf("%s %ld\n",key,tmp->l);   
    }
    else
        printf("Khong co doi bong nay!\n");
}

void f4(){
    int x;
    printf("Nhap so nguyen x: ");
    scanf("%d",&x);
    gvec_t remove=gvec_create(0,NULL);
    rbm_traverse(k,v,t){
        if(v->l<x)
            gvec_append(remove,gtype_s(k->s));
    }
    printf("Doi bi xuong hang:\n");
    gvec_traverse(cur,remove){
        printf("%s\n",cur->s);
        rbm_remove(t,gtype_s(cur->s));
    }
    f2(t);
    gvec_free(remove);
}

void f5(){
    FILE *fo=fopen("KetQua.txt","w");
    rbm_traverse(k,v,t){
        fprintf(fo,"%s\t%ld\n",k->s,v->l);
    }
    fclose(fo);
    printf("Da luu thanh cong danh sach cac doi bong tai mua tiep theo.\n");
}

int main(int argc,char* argv[]){
    int m=0;
    for(;;){
        printf("\n\n=====MENU=====\n");
        printf("1. Tao cay\n");
        printf("2. Ket qua\n");
        printf("3. Tim kiem\n");
        printf("4. Xuong hang\n");
        printf("5. Xuat file\n");
        printf("Lua chon cua ban: ");
        scanf("%d",&m);
        if(m==1){
            f1(argc,argv[1]);
        }
        else if(m==2){
            f2(t);
        }
        else if(m==3){
            f3();
        }
        else if(m==4){
            f4();
        }
        else if(m==5){
            f5();
            break;
        }
        else{
            printf("Lua chon khong hop le! Vui long chon lai!\n");
            continue;
        }
    }
    rbm_traverse(k,v,t){
        free(k->s);
    }
    rbm_free(t);
    printf("fin\n");
    return 0;
}