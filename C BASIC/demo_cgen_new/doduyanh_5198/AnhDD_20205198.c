#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"cgen.h"
#include"ext/io.h"

#define N 30
// RESTRUCTUER
typedef struct _info_{
    float open,close;
    char* id;
    float sub;
}*info;

#define to_info(n) ((info)n)
#define to_info_open(n) (to_info(n)->open)
#define to_info_close(n) (to_info(n)->close)
#define to_info_id(n) (to_info(n)->id)
#define to_info_sub(n) (to_info(n)->sub)
//------------------------------------------------------------
// GLOBAL VAR
rbm_t t;
gvec_t vec;
rbm_t sub;
// char* line=NULL;
int n=0;
//------------------------------------------------------------
    // scanf(" %[^\n]%*c",str);

// FREE FUNCTION
void free_strdup(info I){
    free(to_info_id(I));
    free(I);
}

void free_inside_rbm(rbm_t t){
    rbm_traverse(k,v,t){
        free_strdup(to_info(v->v));
    }
}
//------------------------------------------------------------
//FUNCTIONS
void parse_input(int argc,char *file){
    FILE *fi=fopen(file,"r");
    if(argc!=2){
        printf("Usage: ./prog data.txt\n");
        exit(1);
    }
    fscanf(fi,"%d",&n);
    vec=gvec_create(n,NULL);
    for(int i=0;i<10;i++){
        t=rbm_create(gtype_cmp_s,NULL,NULL);
        float a=0,b=0;
        for(int j=0;j<n;j++){
            info I=malloc(sizeof(struct _info_));
            char key[N];
            fscanf(fi,"%s%f%f",key,&I->open,&I->close);
            I->id=strdup(&key[0]);
            I->sub=I->close-I->open;
            rbm_insert(t,gtype_s(I->id),gtype_v(I));
        }
        gvec_append(vec,gtype_rbm(t));
    }
    fclose(fi);
    sub=rbm_create(gtype_cmp_s,NULL,NULL);
    gvec_traverse(cur,vec){
        rbm_t tmp=cur->rbm;
        rbm_traverse(k,v,tmp){
            gtype* tmp=rbm_value(sub,gtype_s(k->s));
            if(!tmp){
                rbm_insert(sub,gtype_s(k->s),gtype_d(to_info_sub(v->v)));
            }
            else
                tmp->d+=to_info_sub(v->v);
        }
    }

    rbm_traverse(k,v,sub){
        printf("%-5s %-5.3f\n",k->s,v->d/10);
    }
}

void f2(){
    char str[N];
    printf("Nhap ma chung khoan: ");
    scanf(" %[^\n]%*c",str);
    gtype *tmp=rbm_value(sub,gtype_s(str));
    if(!tmp)
        printf("Khong tim thay ma!\n");
    else{
        
    }
}

void f3(){
    printf("Nhung ma co xu huong tang:\n");
    rbm_traverse(k,v,sub){
        if(v->d/10>0)
        printf("%s\n",k->s);
    }
}

void f4(){
    int max=-9999;
    rbm_traverse(k,v,sub){
        if(v->d>max)
            max=v->d;
    }
    rbm_traverse(k,v,sub){
        if(v->d==max)
            printf("Ma co so ngay tang lon nhat: %s\n",k->s);
    }
}

void menu(int argc,char* file){
    int m;
    for(;;){
        printf("\n\n=====MENU=====\n");
        printf("1. Doc file\n");
        printf("2. Tim kiem theo ma chung khoan\n");
        printf("3. Tim kiem nhung ma chung khoan co xu huong tang\n");
        printf("4. Tim ma co so ngay tang lon nhat\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban (1-5): ");
        scanf("%d",&m);
        if(m==1){
            parse_input(argc,file);
        }
        else if(m==2){
            f2();
        }
        else if(m==3){
            f3();
        }
        else if(m==4){
            f4();
        }
        else if(m==5){
            printf("DO DUY ANH 20205198\n");
            break;
        }
        else{
            printf("\nLua chon khong hop le, vui long nhap lai!\n");
            continue;
        }
    }
}

//------------------------------------------------------------
int main(int argc,char* argv[]){     
    menu(argc,argv[1]);
    


    // FREE
    // free(line);

    //------------------------------------------------------------
    return 0;
}