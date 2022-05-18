#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

#define N 30
rbm_t t;
int n=0;
typedef struct _info_{
    long id;
    char *toy;
}*info;
info A;


void print_tree(rbm_t t){    
    printf("\n%-5s%-30s\n--------------------------\n","Id","Toy");
    rbm_traverse(k,v,t){
        printf("%-5ld %-30s\n",k->l,v->s);
    }
}

static int cmp(gtype v1, gtype v2) {
  return v2.l - v1.l;
}

static int cmp_s(const void* v1, const void * v2) {
  return strcmp(((info)v1)->toy,((info)v2)->toy);
}

void free_rbm_v(rbm_t x){
    rbm_traverse(k,v,x){
        gtype *tmp=v;
        free(tmp->v);
    }
}

void free_arr(info a,int size){
    for(int i=0;i<size;i++)
        free(a[i].toy);
}

void f3(){
    gtype *del=calloc(0,sizeof(gtype));
    int count=0;
    for(int i=0;i<n;i++){
        rbm_traverse(k,v,t){
            if(A[i].id==k->l){
                count++;
                del=realloc(del,count*sizeof(gtype));
                printf("Thong tin em nho bi lap: %ld %s\n",k->l,v->s);             
                gtype tmp;
                tmp.l=k->l;
                del[count-1]=tmp;
            }
        }
    }
    for(int i=0;i<count;i++){
        rbm_remove(t,del[i]);
    }
    print_tree(t);
    free(del);
}

void f4(){
    for(int i=0;i<n;i++){
        rbm_insert(t,gtype_l(A[i].id),gtype_s(strdup(A[i].toy)));
    }
    bn_tree_t tree = (bn_tree_t)t;
    rbm_node_t tmp;
    bn_traverse_rnl(cur, tree) {
        tmp = (rbm_node_t)cur;
        printf("%ld - %s\n", (tmp->key).l, (tmp->value).s);
    }
    // free_rbm_v(tmp);
    // rbm_free(tmp);
}

void f5(){
    // info tmp=calloc(0,sizeof(struct _info_));
    // int idx=0;
    // rbm_traverse(k,v,t){
    //     idx++;
    //     tmp=realloc(tmp,idx*sizeof(struct _info_));
    //     tmp[idx-1].id=k->l;
    //     tmp[idx-1].toy=strdup(v->s);
    // }
    // qsort(tmp,rbm_size(t),sizeof(tmp[0]),cmp_s);
    // int count=1;
    // for(int i=0;i<rbm_size(t)-1;i++){
    //     if(strcmp(tmp[i].toy,tmp[i+1].toy)==0){
    //         count++;
    //         if(i==rbm_size(t)-2)
    //         printf("%s %d\n",tmp[i].toy,count);
    //     }
    //     else{
    //         printf("%s %d\n",tmp[i].toy,count);
    //         count=1;
    //         if(rbm_size(t)-2==i)
    //            printf("%s %d\n",tmp[i+1].toy,count);
    //     }
    // }
    // free_arr(tmp,rbm_size(t));
    // free(tmp);
    hmap_t A = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
    rbm_traverse(k, v, t){
        hmap_ires res = hmap_insert(A, gtype_s(v->s), gtype_l(1));
        if(!res.inserted){
            (res.value->l)++;
        }
    }
    hmap_traverse(k, v, A){
        printf("%s\t%ld\n", k->s, v->l);
    }
    hmap_traverse(k, v, A){
        free(k->s);
    }
    hmap_free(A);
}

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("Usage: ./prog A.txt B.txt\n");
        exit(1);
    }
    int m;
    char* line=NULL;
    for(;;){
        printf("\n\n=====MENU=====\n");
        printf("1. Doc file A\n");
        printf("2. Doc file B\n");
        printf("3. Tim kiem\n");
        printf("4. Tong hop\n");
        printf("5. Thong ke\n");
        printf("6. Thoat\n");
        printf("Lua chon cua ban (1-6): ");
        scanf("%d",&m);
        if(m==1){
            t=rbm_create(gtype_cmp_l,NULL,NULL);
            FILE* fi1=fopen(argv[1],"r");
            while(cgetline(&line,0,fi1)){
                struct _info_ I;
                if(line[strlen(line)-1]=='\n')
                    line[strlen(line)-1]='\0';
                if(strstr(line," ")){
                    tok_traverse(cur,line,ascii_spaces){
                        I.id=atol(cur);
                        cur=strtok(NULL,ascii_spaces);
                        I.toy=cur;                       
                    }                   
                }
                else{
                    I.id=atol(line);
                    printf("Id.%ld thieu thong tin! Nhap them thong tin: ",I.id);
                    scanf(" %[^\n]%*c",I.toy);
                }
                rbm_insert(t,gtype_l(I.id),gtype_s(strdup(I.toy)));
            }
            fclose(fi1);
            print_tree(t);
        }
        
        else if(m==2){
            A=calloc(0,sizeof(struct _info_));
            FILE *fi2=fopen(argv[2],"r");
            while(cgetline(&line,0,fi2)){
                n++;
                A=realloc(A,n*sizeof(struct _info_));
                struct _info_ I;
                if(line[strlen(line)-1]=='\n')
                    line[strlen(line)-1]='\0';
                if(strstr(line," ")){
                    tok_traverse(cur,line,ascii_spaces){
                        I.id=atol(cur);
                        cur=strtok(NULL,ascii_spaces);
                        I.toy=cur;                       
                    }                   
                }
                else{
                    I.id=atol(line);
                    printf("Id.%ld thieu thong tin! Nhap them thong tin: ",I.id);
                    scanf(" %[^\n]%*c",I.toy);
                }
                A[n-1].id=I.id;
                A[n-1].toy=strdup(I.toy);
            }
            fclose(fi2);
            
            printf("\n%-5s%-30s\n--------------------------\n","Id","Toy");
            for(int i=0;i<n;i++)  
                printf("%-5ld %-30s\n",A[i].id,A[i].toy);
    
        }

        else if(m==3){
            f3();
        }
        else if(m==4){
            f4();
        }
        else if(m==5){
            f5();
        }
        else if(m==6){    
            break;
        }
        else{
            printf("\nLua chon khong hop le, vui long nhap lai!\n");
            continue;
        }
    }
    free_arr(A,rbm_size(t));
    free(A);
    // free_rbm_v(t);
    // rbm_free(t);
    free(line);
    printf("fin\n");
    return 0;
}

// chua free