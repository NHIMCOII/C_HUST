#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

typedef struct _info_{
    int date;
    char* code;
    int patients; 
}*info;

rbm_t t;

#define to_info(n) ((info)n)
#define to_info_date(n) (to_info(n)->date)
#define to_info_code(n) (to_info(n)->code)
#define to_info_patients(n) (to_info(n)->patients)


static int gtype_cmp_v(gtype v1, gtype v2) {
    int x=to_info_date(v1.v)-to_info_date(v2.v);
    int y=strcmp(to_info_code(v1.v),to_info_code(v2.v));
  if(x==0){
      return y;
  }
  else {
      return x;
  }
}

void free_strdup(info I){
    free(to_info_code(I));
    free(I);
}

void free_inside_rbm(rbm_t t){
    rbm_traverse(k,v,t){
        free_strdup(to_info(v->v));
    }
}
void f1(char* key){
    info I=malloc(sizeof(struct _info_));
    tok_traverse(cur,key,ascii_spaces){
        cur=strtok(NULL,ascii_spaces);
        I->code=strdup(cur);
        cur=strtok(NULL,ascii_spaces);
        I->date=atoi(cur);
        cur=strtok(NULL,ascii_spaces);
        I->patients=atoi(cur);
    }
    rbm_insert(t,gtype_v(I),gtype_l(I->patients));  
}

void f2(){
    int count=0;
    rbm_traverse(k,v,t){
        count+=v->l;
    }
    printf("Total patients: %d\n",count);
}

void f3(char*key){
    info I=malloc(sizeof(struct _info_));
    tok_traverse(cur,key,ascii_spaces){
        cur=strtok(NULL,ascii_spaces);
        I->code=cur;
        cur=strtok(NULL,ascii_spaces);
        I->date=atoi(cur);
    }
    gtype*count = rbm_value(t,gtype_v(I));
    printf("Number of patients in %s on day %d: %d\n",I->code,I->date,count->l);
    free(I);
}

void f4(char*key){
    int start,end;
    tok_traverse(cur,key,ascii_spaces){
        cur=strtok(NULL,ascii_spaces);
        start=atoi(cur);
        cur=strtok(NULL,ascii_spaces);
        end=atoi(cur);
    }
    int count=0;
    rbm_traverse(k,v,t){
        if(to_info_date(k->v)>=start&&to_info_date(k->v)<=end){
            count+=v->l;
        }
    }
    printf("Number of patients from day %d to %d: %d\n",start,end,count);
}

void f5(char*key){
    char *reg;
    int count=0;
    tok_traverse(cur,key,ascii_spaces){
        cur=strtok(NULL,ascii_spaces);
        reg=cur;
    }
    rbm_traverse(k,v,t){
        if(strcmp(to_info_code(k->v),reg)==0){
            count+=v->l;
        }
    }
    printf("Number of patients in %s: %d\n",reg,count);
}

int main(int argc, char* argv[]){
    if(argc!=1){
        printf("Usage: ./prog\n");
        exit(1);
    }
    t=rbm_create(gtype_cmp_v,NULL,NULL);
    while(1){
        char key[100];
        printf("INPUT > ");
        scanf(" %[^\n]%*c",key);
        if(strstr(key,"$Update")){
            f1(key);
        }
        else if(strstr(key,"$CountTotalPatients")){
            f2();
        }
        else if(strstr(key,"$FindNumberPatients")){
            f3(key);
        }
        else if(strstr(key,"$CountNumberPatientsOfPeriod")){
            f4(key);
        }
        else if(strstr(key,"$CountNumberPatientsOfRegion")){
            f5(key);
        }
        else if(strcmp(key,"***")==0){
            break;
        }
        else{
            printf("Invalid Input! Try again!\n");
            continue;
        }
    }
    free_inside_rbm(t);
    rbm_free(t);
    return 0;
}
