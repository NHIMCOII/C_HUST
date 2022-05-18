#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"cgen.h"
#include"ext/io.h"

#define N 40

typedef struct _info_{
    char place[N];
    int hour,min;
} *info;
info A;

gdl_t list;
#define to_info(a) ((info)a)
int cmp_func(const void *a,const void *b){
    if(to_info(a)->hour<to_info(b)->hour)
        return -1;
    if(to_info(a)->hour==to_info(b)->hour){
        if(to_info(a)->min<to_info(b)->min)
            return -1;
        if(to_info(a)->min>to_info(b)->min)
            return 1;
    }
    if(to_info(a)->hour>to_info(b)->hour)
        return 1;
}

gtype create_node(char *place,int hour,int min){
    info nn=malloc(sizeof(struct _info_));
    strcpy(nn->place,place);
    nn->hour=hour;
    nn->min=min;
    return (gtype){.v=(void *)nn};
}

void gdl_delete_node(gdl_t list,gtype *pos){
    if(pos == list->front){
        gdl_pop_front(list);
        return;
    }
    else if(pos== list->back){
        gdl_pop_back(list);
        return;
    }
    else if(gdn_next(pos)==NULL&&gdn_prev(pos)==NULL){
        free(pos);
        list->back=list->front=NULL;
        return;
    }
    else{
        gdl_traverse(cur,list){
            if(pos==cur){
                gdn_next(gdn_prev(pos))=gdn_next(pos);
                gdn_prev(gdn_next(pos))=gdn_prev(pos);
            }
        }
        free(pos);
    }
}

void f1(char *file){
    int n=0;
    A=calloc(n,sizeof(struct _info_));
    FILE *fi=fopen(file,"r");
    while(!feof(fi)){
        n++;
        A=realloc(A,n*sizeof(struct _info_));
        struct _info_ tmp;
        fscanf(fi,"%s%d%d",tmp.place,&tmp.hour,&tmp.min);
        strcpy(A[n-1].place,tmp.place);
        A[n-1].hour=tmp.hour;
        A[n-1].min=tmp.min;
    }
    qsort(A,n,sizeof(A[0]),cmp_func);
    for(int i=0;i<n;i++){
        gdl_push_back(list,create_node(A[i].place,A[i].hour,A[i].min));
    }
    fclose(fi);

    printf("Doc thanh cong du lieu!\n");
}

void f2(){
    printf("\nLich trinh di chuyen: \n");
    printf("%-50s%-10s%-10s\n","Dia diem","Gio","Phut");
    printf("----------------------------------------------------------------------------\n");
    gdl_traverse(cur,list){
        info tmp=cur->v;
        printf("%-50s%-10d%-10d\n",tmp->place,tmp->hour,tmp->min);
    }
}

void f3(){
    char str[N];
    printf("Nhap dia diem: ");
    scanf(" %[^\n]%*c",str);
    int flag=0;
    gdl_traverse(cur,list){
        info tmp=cur->v;
        if(strcmp(tmp->place,str)==0){
            if(flag!=0)printf(", ");
            printf("%d:%d",tmp->hour,tmp->min);
            flag++;
        }
    }
    if(flag==0)printf("Ban chua toi dia diem do!\n");
}

void f4(){
    int h,m;
    do{
        printf("Nhap gio va phut: ");
        scanf("%d%d",&h,&m);
    }while(h<0||h>=24||m<0||m>=60);
    int flag=0;
    gdl_traverse(cur,list){
        info tmp=cur->v;
        if(tmp->hour==h&&tmp->min<=m){
            printf("%s\n",tmp->place);
            flag++;
        }
    }
    if(flag==0) printf("KHONG tim thay lich su di chuyen!\n");
}

void f5(){
    char str[N];
    int h,m;
    printf("Nhap dia diem: ");
    scanf(" %[^\n]%*c",str);
    do{
        printf("Nhap gio va phut: ");
        scanf("%d%d",&h,&m);
    }while(h<0||h>=24||m<0||m>=60);
    gdl_traverse(cur,list){
        info tmp=cur->v;
        if(strcmp(tmp->place,str)==0){
            if(h<tmp->hour){
                printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");               
                return;       
            }
            if(h==tmp->hour){
                if(m<tmp->min){
                    printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");               
                    return; 
                }
            }
        }
    }
    printf("Lich su di chuyen cua ban OK!\n");
}

int main(int argc , char*argv[]){
    if(argc!=2){
        printf("Usage: ./prog log.txt\n");
        exit(1);
    }
    list=gdl_create(gtype_free_v);
    int m,flag=0;
    for(;;){
        printf("\n\n=====MENU=====\n");
        printf("1. Nap du lieu log lich su di chuyen\n");
        printf("2. In ra lich su di chuyen\n");
        printf("3. Tim kiem lich su di chuyen theo dia diem\n");
        printf("4. Tim kiem thong tin di chuyen theo thoi gian\n");
        printf("5. Kiem tra truy vet moi nhat\n");
        printf("6. Thoat\n");
        printf("Lua chon cua ban (1-6): ");
        scanf("%d",&m);
        if(m==1){
            if(flag==0){
                f1(argv[1]);
                flag++;
            }
            else{
                printf("Da nap du lieu!\n");
            }
        }
        else if(m==2){
            if(flag!=0)
            f2();
        }
        else if(m==3){
            if(flag!=0)
            f3();
        }
        else if(m==4){
            if(flag!=0)
            f4();
        }
        else if(m==5){
            if(flag!=0)
            f5();
        }
        else if(m==6){
            if(flag!=0){
                gdl_free(list);
                free(A);
            }
            break;
        }
        else{
            printf("\nLua chon khong hop le, vui long nhap lai!\n");
            continue;
        }
    }
    return 0;
}
