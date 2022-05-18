#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

int n,num;
typedef struct _info_{
    int store;
    gsl_t list;
}*info;
info A;
typedef struct _path_{
    int store;
    char *prod;
}*path;
path P;

void print_info(){
    for(int i=0;i<n;i++){
        printf("%d ",A[i].store);
        gsl_traverse(cur,A[i].list){
            printf("%s->",cur->s);
        }
        printf("\n");
    }
}

int check_store_name(int name){
    for(int i=0;i<n;i++){
        if(A[i].store==name)
            return 1;
    }
    return 0;
}

int check_product(char *key){
    for(int i=0;i<n;i++){
        gsl_traverse(cur,A[i].list){
            gtype *tmp=cur;
            if(strcmp(key,tmp->s)==0)
                return 1;
        }
    }
    return 0;
}

void gsl_delete_node(gsl_t list,gtype *pos){
    if(pos == list->front){
        gsl_pop_front(list);
        return;
    }
    else if(pos== list->back){
        gtype *tmp=NULL;
        gsl_traverse(cur,list){
            if(gsn_next(cur)==list->back)
                tmp=cur;
        }
        gsn_next(tmp)=NULL;
        list->back=tmp;
        free(pos);
        return;
    }
    else if(gsn_next(pos)==NULL){
        free(pos);
        list->back=list->front=NULL;
        return;
    }
    else{
        gtype *tmp=NULL;
        gsl_traverse(cur,list){
            if(pos==cur){
                gsn_next(tmp)=gsn_next(pos);
            }
            tmp=cur;
        }
        free(pos);
    }
}

int get_idx(int name){
    for(int i=0;i<n;i++)
        if(A[i].store==name)
            return i; 
}

int check_path(int n){
    for(int i=0;i<n-1;i++){
        if(strcmp(P[i].prod,P[i+1].prod)==0){
            printf("Vi pham 1!\n");
            return 0;
        }
    }
    for(int i=0;i<n-2;i++){
        if(P[i].store==P[i+1].store||P[i].store==P[i+2].store){
            printf("Vi pham 2!\n");
            return 0;
        } 
    }
    return 50*n;
}

void f1(){
    int name;
    printf("\nNhap ten cua hang: ");
    scanf("%d",&name);
    if(check_store_name(name)==0){
        printf("Khong ton tai cua hang!\n");
        return;
    }
    printf("Mon hang tai cua hang %d: ",name);
    int idx=get_idx(name);
    if(gsl_is_empty(A[idx].list)){
        printf("Khong con san pham!\n");
        return;
    }
    gsl_traverse(cur,A[idx].list){
        printf("%s -> ",cur->s);
    }
}

void f2(){
    int name,flag=0;
    char key[1];
    printf("\nNhap ten cua hang: ");
    scanf("%s",key);
    if(strcmp(key,"Q")==0) return;
    name=atoi(key)-1;
    if(check_store_name(name+1)==0){
        printf("Cua hang khong ton tai!\n");
        return;
    }
    char str[1];
    printf("Nhap ten mon hang can xoa: ");
    scanf("%s", str);
    if(strcmp(str,"Q")==0) return;
    gtype *tmp=NULL;
    gsl_traverse(cur,A[name].list){
        if(strcmp(str,cur->s)==0){
            tmp=cur;
            flag++;
        }
    }
    if(flag==0)
        printf("Khong ton tai mon hang can tim!\n");
    else{
        gsl_delete_node(A[name].list,tmp);
    }
    print_info();
}

void f3(){
    int name,flag=0;
    char key[1];
    printf("Nhap ten cua hang can them: ");
    scanf("%s",key);
    if(strcmp(key,"Q")==0) return;
    name=atoi(key)-1;
    if(check_store_name(name+1)==1){
        printf("Da ton tai cua hang!\n");
        return;
    }
    n++;
    A=realloc(A,n*sizeof(struct _info_));
    A[n-1].store=name+1;
    A[n-1].list=gsl_create(gtype_free_s);
    printf("Nhap cac mon hang can them: \n");
    while(1){
        char key[1];
        printf("> ");
        scanf("%s",key);
        if(strcmp(key,"Q")==0){
            print_info();   
            return;
        } 
        if(check_product(key)){
            gsl_push_back(A[n-1].list,gtype_s(strdup(key)));
        }
        else{
            printf("Mat hang ko dap ung yeu cau!\n");
        }
    } 
}

void f4(){
    int name;
    char *s;
    do{
        printf("Nhap so luong cua hang can kiem tra: ");
        scanf("%d",&num);
    }while(num<0);
    P=calloc(num,sizeof(struct _path_));
    for(int i=0;i<num;i++){
        do{
            printf("Ten cua hang: ");
            scanf("%d",&name);
        }while(check_store_name(name)==0);
        do{
            printf("Mon hang kiem tra: ");
            scanf("%s",s);
        }while(check_product(s)==0);
        P[i].store=name;
        P[i].prod=strdup(s);
    }
    
    int result= check_path(num);

    if(result==0)
        printf("Lo trinh khong hop le!\n");  
    else{
        printf("Tong chi phi di lai = %d\n",result);
    }

}

int main(int argc,char* argv[]){
    FILE *fi=fopen(argv[1],"r");
    if(argc!=2){
        printf("Usage: ./prog inp.txt\n");
        exit(1);
    }
    fscanf(fi,"%d\n",&n);
    A=calloc(n,sizeof(struct _info_));
    int idx=0;
    char *line=NULL;
    while(cgetline(&line,0,fi)){
        if(line[strlen(line)-1]=='\n')    
            line[strlen(line)-1]='\0';
        int flag=0;
        tok_traverse(cur,line," "){          
            if(flag==0){
                A[idx].store=atoi(cur);
                flag++;
            }
            else{
                A[idx].list=gsl_create(gtype_free_s);
                tok_traverse(tok,cur,","){
                    gsl_push_back(A[idx].list,gtype_s(strdup(tok)));  
                }
            }
        }
        idx++;
    }
    fclose(fi);
    
    int m;
    for(;;){
        printf("\n\nBan hay nhap chuc nang can thuc hien\n");
        printf("1. Xac dinh cac mon hang trong cua hang\n");
        printf("2. Xoa di cac mon hang cua mot cua hang\n");
        printf("3. Them mot cua hang va cac mon hang trong do\n");
        printf("4. Tinh toan chi phi di lai\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban (1-5): ");
        scanf("%d",&m);
        if(m==1){
            f1();
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
            break;
        }
        else{
            printf("\nLua chon khong hop le, vui long nhap lai!\n");
            continue;
        }
    }
    for(int i=0;i<num;i++){
        free(P[i].prod);
    }
    free(P);
    for(int i=0;i<n;i++){
        gsl_free(A[i].list);
    }
    free(A);
    free(line);
    return 0;
}