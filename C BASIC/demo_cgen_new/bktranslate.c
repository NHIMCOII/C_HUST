#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"cgen.h"
#include"ext/io.h"

typedef struct _info_{
    char vn[25],
        eng[25];
}*dict;
dict D;

int n=0;

int cmp_func(const void *a,const void *b){
    return strcmp(((dict)a)->eng,((dict)b)->eng);
}

int check_input(char* key){
    for(int i=0;i<n;i++){
        if(strcmp(D[i].eng,key)==0)
            return i;
    }
    return -1;
}

char *tolower_str(char* str){
    int i=0;
    while(str[i]){
        str[i]=tolower(str[i]);
        i++;
    }
    return str;
}

void f1(int argc,char* argv[]){
    FILE *fi=fopen(argv[1],"r");
    while(!feof(fi)){
        n++;
        D=realloc(D,n*sizeof(struct _info_));
        fscanf(fi,"%s",D[n-1].eng);
        printf("%-25s",D[n-1].eng);
        fscanf(fi,"%s",D[n-1].vn);
        printf("%-25s\n",D[n-1].vn);
    }
    fclose(fi);
}

void f2(){
    qsort(D,n,sizeof(D[0]),cmp_func);
    for(int i=0;i<n;i++){
        printf("%-25s %-25s\n",D[i].eng,D[i].vn);
    }
}

void f3(char *file){
    char key[25],c;
    printf("Nhap 1 tu tieng anh: ");
    scanf("%s",key);
    int result=check_input(key);
    if(result!=-1){
        printf("Tu da ton tai trong tu dien!\n");
        printf("Ban co muon nhap noi dung moi cho tu nay khong ?(y/n) ");
        scanf(" %c",&c);
        if(c=='y'){
            printf("Nhap noi dung moi cho tu %s: ",D[result].eng);
            char tmp[25];
            scanf("%s",tmp);
            strcpy(D[result].vn,tolower_str(tmp));
        }       
   }
   else{
       n++;
       D=realloc(D,n*sizeof(struct _info_));
       strcpy(D[n-1].eng,tolower_str(key));
       printf("Nhap nghia cua tu: ");
       char tmp[25];
       scanf("%s",tmp); 
       strcpy(D[n-1].vn,tolower_str(tmp));
       FILE *fi=fopen(file,"a");
       fprintf(fi,"\n%s %s",D[n-1].eng,D[n-1].vn); 
       fclose(fi);
   }
}

void f4(){
    char str[100];
    printf("Enter sentence: ");
    scanf(" %[^\n]%*c",str);
    printf("%-25s %-25s\n----------------------------------\n","ENG","VN");
    tok_traverse(cur,str,ascii_spaces){
        cur=tolower_str(cur);
        printf("%-25s",cur);
        int idx=check_input(cur);
        if(idx==-1)printf("<thieu tu>\n");
        else{
            printf("%s\n",D[idx].vn);
        }
    }
}

int main(int argc,char* argv[]){
    system("CHCP 65001");
    if(argc!=2){
        printf("Usage: ./prog dict.txt\n");
        exit(1);
    }
    D=calloc(n,sizeof(struct _info_));
    int m=0;
    for(;;){
        printf("\n\n======BKTRANSLATE======\n\n");
        printf("1. Nạp từ điển\n");
        printf("2. Noi dung tu dien\n");
        printf("3. Them / Sua tu\n");
        printf("4. Dich cau Anh-Viet\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban (1-5): ");
        scanf("%d",&m);
        printf("\n");
        if(m==1){
            f1(argc,argv);
        }
        else if(m==2){
            f2();
        }
        else if(m==3){
            f3(argv[1]);
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

    free(D);
    return 0;
}