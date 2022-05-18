#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"cgen.h"
#include"ext/io.h"

#define N 30
// RESTRUCTUER
typedef struct _info_{
    int day;
    float open,close;
    // char *id;
    // gvec_t *ptr_gvec;
}*info;

#define to_info(n) ((info)n)
#define to_info_open(n) (to_info(n)->open)
#define to_info_close(n) (to_info(n)->close)
#define to_info_day(n) (to_info(n)->day)
// #define to_info_id(n) (to_info(n)->id)
// #define to_info_gvec(n) (to_info(n)->ptr_gvec)
//------------------------------------------------------------
// GLOBAL VAR
rbm_t tree;
int n=0;
char *line=NULL;
//------------------------------------------------------------
    // scanf(" %[^\n]%*c",str);

// FREE FUNCTION

//------------------------------------------------------------
//FUNCTIONS

void parse_input(int argc,char *file){
    FILE *fi=fopen(file,"r");
    if(argc!=2){
        printf("Usage: ./prog data.txt\n");
        exit(1);
    }
    fscanf(fi,"%d",&n);
    tree=rbm_create(gtype_cmp_s,NULL,NULL);
    int idx=0;
    gvec_t *A[n];
    for(int i=0;i<n;i++){
        A[i]=NULL;
    }
    while(cgetline(&line,0,fi)){
        char *id=NULL;
        printf("ye0\n");  

        info I=malloc(sizeof(struct _info_));
        tok_traverse(cur,line,ascii_spaces){
            id=strdup(cur);
            cur=strtok(NULL,ascii_spaces);
            I->open=atof(cur);
            cur=strtok(NULL,ascii_spaces);
            I->close=atof(cur);
        }   
        printf("ye1\n");  
        gtype* check=rbm_value(tree,gtype_s(id));//=======================
        printf("ye2\n");  

        
        if(!check){
        printf("ye3\n");  
            
            // *A[idx]=gvec_create(10,NULL);
        printf("ye5\n");  
            check->gvec=gvec_create(10,NULL);
            I->day=1;

            gvec_append(check->gvec,gtype_v(I));
        printf("ye6\n");  

            rbm_insert(tree,gtype_s(id),gtype_gvec(check->gvec));
        printf("ye7\n");  
            
            idx++;
        }
        else{      
        printf("ye4\n");  

            gvec_t tmp=check->gvec;
            I->day++;
            gvec_append(tmp,gtype_v(I));
        }        
        
    }   
    fclose(fi);

    // rbm_traverse(k,v,tree){
    //     printf("%s ",k->s);
    //     gvec_t tmp=v->gvec;
    //     gvec_traverse(cur,tmp){
    //         printf("Day %d: %.3f -> %.3f\n",to_info_day(cur->v),to_info_open(cur->v),to_info_close(cur->v));
    //     }
    // }
}


void f2(){
    
}

void f3(){
    printf("Nhung ma co xu huong tang:\n");
   
}

void f4(){
    
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
            // f2();
        }
        else if(m==3){
            // f3();
        }
        else if(m==4){
            // f4();
        }
        else if(m==5){
            printf("- DO DUY ANH 20205198 - \n");
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