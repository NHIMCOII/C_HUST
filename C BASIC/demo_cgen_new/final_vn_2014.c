#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

#define N 30

typedef struct _info_{
    char *Username;
    char *Password;
    float Diem;
}*info;

rbm_t t;

#define to_info(n) ((info)n)
#define to_info_username(n) (to_info(n)->Username)
#define to_info_password(n) (to_info(n)->Password)
#define to_info_diem(n) (to_info(n)->Diem)

void free_strdup(info I){
    free(to_info_username(I));
    free(to_info_password(I));
    free(I);
}

void free_inside_rbm(rbm_t t){
    rbm_traverse(k,v,t){
        free_strdup(to_info(v->v));
    }
}

void print_rbm(rbm_t t){
    rbm_traverse(k,v,t){
        printf("%-20s %-20s %-5.1f\n",k->s,to_info_password(v->v),to_info_diem(v->v));
    }
}


void sv1(gtype *res){
    printf("%s: %.1f\n",to_info_username(res->v),to_info_diem(res->v));
}

void sv2(gtype *res){
    char pass[N],pass2[N];
    printf("Nhap mat khau moi: ");
    scanf(" %[^\n]%*c",pass);
    printf("Nhap  lai mat khau moi: ");
    scanf(" %[^\n]%*c",pass2);
    if(strstr(pass," ")){
        printf("Mat khau moi chua ky tu trang!\n");
        return;
    }
    if(strcmp(pass,pass2)==0){
        printf("Thay doi mat khau thanh cong!\n");
        strcpy(to_info_password(res->v),pass);
    }
    else{
        printf("Thay doi mat khau khong thanh cong!\n");
    }
}

void sv3(char *file){
    FILE *fi=fopen(file,"w");
    int flag=0;
        rbm_traverse(k,v,t){
            if(flag==0)
                fprintf(fi,"%s\t%s\t%.1f",to_info_username(v->v),to_info_password(v->v),to_info_diem(v->v));
            else
                fprintf(fi,"\n%s\t%s\t%.1f",to_info_username(v->v),to_info_password(v->v),to_info_diem(v->v));
            flag++;
        }
        fclose(fi);
}

void sinh_vien(gtype *res,char* file){
    int m=0;
    for(;;){
        printf("\n\n=====Sinh vien=====\n");
        printf("Username: %s\n",to_info_username(res->v));
        printf("1. Xem diem\n");
        printf("2. Thay doi mat khau\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d",&m);
        if(m==1){
            sv1(res);
        }
        else if(m==2){
            sv2(res);
        }
        else if(m==3){
            sv3(file);
            break;
        }

        else{
            printf("Lua chon khong hop le! Vui long chon lai!\n");
            continue;
        }
    }
}

void ad1(){
    char user[N],pass[N];
    float diem;
    info I=malloc(sizeof(struct _info_));
    printf("\nNhap thong tin sinh vien:\n");
    printf("Username: ");
    scanf(" %[^\n]%*c",user);
    if(strstr(user," ")){
        printf("Username chua ky tu trang!\n");
        return;
    }
    I->Username=strdup(&user[0]);//**********************************************************
    printf("Password: ");
    scanf(" %[^\n]%*c",pass);
    if(strstr(pass," ")){
        printf("Password chua ky tu trang!\n");
        return;
    }
    I->Password=strdup(&pass[0]);
    printf("Diem: ");
    scanf("%f",&I->Diem);   
    rbm_insert(t,gtype_s(I->Username),gtype_v(I));  
    printf("Them thong tin sinh vien thanh cong!\n");
}


void ad2(){
    rbm_traverse(k,v,t){
        if(strcmp(to_info_username(v->v),"Admin")!=0){
            printf("%-20s %-20s %-5.1f\n",k->s,to_info_password(v->v),to_info_diem(v->v));
        }
    }
}

void ad3(){
    char user[N];
    printf("Nhap username can xoa: ");
    scanf(" %[^\n]%*c",user);
    gtype *tmp=rbm_value(t,gtype_s(user));
    if(tmp){
        if(strcmp(to_info_username(tmp->v),"Admin")==0){
            printf("Khong duoc xoa admin!\n");
            return;
        }
        else{
            printf("Thong tin sinh vien vua xoa: \n");
            printf("%s\t%s\t%.1f\n",to_info_username(tmp->v),to_info_password(tmp->v),to_info_diem(tmp->v));
            gtype* tmp=rbm_value(t,gtype_s(user));
            free_strdup(tmp->v);
            rbm_remove(t,gtype_s(user));
        }
    }
    else
        printf("Khong ton tai username!\n");
}

void ad4(char* file){
    sv3(file);
}

void admin(char *file){
    int m=0;
    for(;;){
        printf("\n\n=====Admin=====\n");
        printf("1. Them sinh vien\n");
        printf("2. In danh sach sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d",&m);
        if(m==1){
            ad1();
        }
        else if(m==2){
            ad2();
        }
        else if(m==3){
            ad3();
        }
        else if(m==4){
            ad4(file);
            break;
        }
        else{
            printf("Lua chon khong hop le! Vui long chon lai!\n");
            continue;
        }
    }
}

int main(int argc,char* argv[]){
    FILE *fi=fopen(argv[1],"r");
    if(argc!=2){
        printf("Usage: ./prog sinhvien.txt\n");
        exit(1);
    }
    t=rbm_create(gtype_cmp_s,NULL,NULL);
   char*line=NULL;
    while(cgetline(&line,0,fi)){
        info I=malloc(sizeof(struct _info_));
        tok_traverse(cur,line,ascii_spaces){
            I->Username=strdup(cur);
            cur=strtok(NULL,ascii_spaces);
            I->Password=strdup(cur);
            cur=strtok(NULL,ascii_spaces);
            I->Diem=atof(cur);
        }
        rbm_insert(t,gtype_s(I->Username),gtype_v(I));
    }
    fclose(fi);
    int m=0;
    for(;;){
        printf("\n=====MENU=====\n\n");
        printf("1. Dang nhap\n");
        printf("2. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d",&m);
        int flag=0;
        if(m==1){
            char user[N],pass[N];
            for(;;){

                printf("\n\n=====Dang nhap=====\n");
                printf("Username: ");
                scanf(" %[^\n]%*c",user);
                printf("Password: ");
                scanf(" %[^\n]%*c",pass);
                gtype *res=rbm_value(t,gtype_s(user));
                if(res&&strcmp(to_info_password(res->v),pass)==0){   
                    if(strcmp(user,"Admin")!=0){
                        printf("Dang nhap thanh cong!\n");
                        sinh_vien(res,argv[1]);
                        break;
                    }
                    else{
                        admin(argv[1]);
                        break;
                    }
                }
                else{
                    printf("Nhap sai mat khau hoac username!\n");
                    flag++;
                    if(flag==3){
                        printf("Ban da nhap sai qua 3 lan!\n");
                        break;
                    }
                }
            }
            if(flag==3) break;
        }

        else if(m==2){
            break;
        }

        else{
            printf("Lua chon khong hop le! Vui long chon lai!\n");
            continue;
        }
    }

    free_inside_rbm(t);
    rbm_free(t);
    free(line);
    printf("fin\n");
    return 0;
}