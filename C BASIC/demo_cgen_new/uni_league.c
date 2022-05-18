#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

typedef struct _info_{
    int id;
    char *name;
    int score;
    int goal;
    int lose;
}*info;

typedef struct _sched_{
    int t1,t2;
    char* n1,*n2;
}*S;

gsl_t list;
gvec_t sched;
int n;

#define to_info(n) ((info)n)
#define to_info_id(n) (to_info(n)->id)
#define to_info_name(n) (to_info(n)->name)
#define to_info_score(n) (to_info(n)->score)
#define to_info_goal(n) (to_info(n)->goal)
#define to_info_lose(n) (to_info(n)->lose)


#define to_S(n) ((S)n)
#define to_S_n1(n) (to_S(n)->n1)
#define to_S_n2(n) (to_S(n)->n2)

gtype create_info_g(int id,char *name,int score,int goal,int lose){
    info nn=malloc(sizeof(struct _info_));
    nn->id=id;
    nn->name=strdup(name);
    nn->score=score;
    nn->goal=goal;
    nn->lose=lose;
    return (gtype){.v=(void *)nn};
}

void free_info_g(gtype g){
    free(to_info_name(g.v));
    free(g.v);
}

void free_strdup(S I){   
    free(to_S_n1(I));
    free(to_S_n2(I));
    free(I);
}

void free_inside_gvec(gvec_t v){
    gvec_traverse(cur,v){
        free_strdup(to_S(cur->v));
    }
}

void free_strdup2(info I){   
    free(to_info_name(I));
    free(I);
}

void free_inside_gsl(gsl_t l){
    gsl_traverse(cur,l){
        free_strdup2(to_info(cur->v));
    }
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

void f1(){
    printf("%-5s%-20s%-10s%-20s%-20s\n","Id","Team","Score","Goal","Lose");
    gsl_traverse(cur,list){
        printf("%-5d%-20s%-10d%-20d%-20d\n",to_info_id(cur->v),to_info_name(cur->v),to_info_score(cur->v),to_info_goal(cur->v),to_info_lose(cur->v));
    }
}

void f2(){
    int flag=0;
    int i=1;
    gvec_traverse(cur,sched){
        S tmp=(S)cur->v;
        if(flag%(n/2)==0){
             printf("\nVong %d\n",i);
             i++;
        }
        printf("%s - %s\n",tmp->n1,tmp->n2);
        flag++;
    }
}

void f3(){
    int flag=0;
    int i=1,a,b;
    gvec_traverse(cur,sched){
        S tmp=(S)cur->v;
        if(flag%(n/2)==0){
             printf("\nCap nhat ket qua Vong %d:\n",i);
             i++;
        }
        printf("%s - %s: ",tmp->n1,tmp->n2);
        scanf("%d%d",&a,&b);
        int x,y;
        if(a>b){
            x=3;y=0;
        }
        else if(a<b){
            x=0;y=3;
        }
        else{
            x=1;y=1;
        }
        gsl_traverse(cur2,list){
            if(tmp->t1==to_info_id(cur2->v)){
                to_info_score(cur2->v)+=x;
                to_info_goal(cur2->v)+=a;
                to_info_lose(cur2->v)+=b;
            }
            if(tmp->t2==to_info_id(cur2->v)){
                to_info_score(cur2->v)+=y;
                to_info_goal(cur2->v)+=b;
                to_info_lose(cur2->v)+=a;
            }
        }
        flag++;
    }
    f1();
}

void f4(){
    int min =9999;
    gtype **del=calloc(0,sizeof(gtype*));
    gsl_traverse(cur,list){
        if(to_info_score(cur->v)<min)min=to_info_score(cur->v);
    }
    int idx=0;
    printf("Cac doi co diem thap nhat:\n");
    printf("%-5s%-20s%-10s%-20s%-20s\n","Id","Team","Score","Goal","Lose");
    gsl_traverse(cur,list){
        if(min==to_info_score(cur->v)){
            printf("%-5d%-20s%-10d%-20d%-20d\n",to_info_id(cur->v),to_info_name(cur->v),to_info_score(cur->v),to_info_goal(cur->v),to_info_lose(cur->v));           
            idx++;
            del=realloc(del,idx*sizeof(gtype));
            del[idx-1]=cur;
        }
    }
    for(int i=0;i<idx;i++){
        // info tmp=*del[i]->v;
        // free(tmp->name);
        gsl_delete_node(list,del[i]);
    }
    free(del);

    printf("\nCac doi con lai:\n");
    f1();
}

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: ./prog league.txt\n");
        exit(1);
    }
    list=gsl_create(free_info_g);
    sched=gvec_create(0,NULL);
    FILE *fi=fopen(argv[1],"r");
    fscanf(fi,"%d\n",&n);
    if(n%2!=0){
        printf("So doi bong khong phai so chan!\n");
        return 0;
    }
    char *line=NULL;
    int flag=0;
    int k=0;
    while(cgetline(&line,0,fi)){
        remove_tail_lf(line);
        if(flag<n){
            struct _info_ I;
            tok_traverse(cur,line,ascii_spaces){
                I.id=atoi(cur);
                cur=strtok(NULL,ascii_spaces);
                I.name=strdup(cur);
                cur=strtok(NULL,ascii_spaces);
                strcat(I.name," ");
                strcat(I.name,cur);
            }
            gsl_push_back(list,create_info_g(I.id,I.name,0,0,0));
        }
        else{
            if(k%3==0){
                k++;
                continue;
            }
            else{
                S s=malloc(sizeof(struct _sched_));
                tok_traverse(cur,line,ascii_spaces){
                    s->t1=atol(cur);
                    cur=strtok(NULL,ascii_spaces);
                    s->t2=atol(cur);
                    gsl_traverse(cur2,list){
                        if(s->t1==to_info_id(cur2->v))
                            s->n1=strdup(to_info_name(cur2->v));
                        if(s->t2==to_info_id(cur2->v))
                            s->n2=strdup(to_info_name(cur2->v));
                    }
                }
                gvec_append(sched,gtype_v(s));
            }
            k++;
        }
        flag++;
    }
    fclose(fi);
    int m=0;
    for(;;){
        printf("\n\n=====MENU=====\n");
        printf("1. In thong tin doi bong\n");
        printf("2. In thong tin lich thi dau\n");
        printf("3. Cap nhat ket qua vong dau\n");
        printf("4. Thong ke\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");
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
            printf("Lua chon khong hop le! Vui long chon lai!\n");
            continue;
        }
    }

    free_inside_gsl(list);
    gsl_free(list);
    free_inside_gvec(sched);
    gvec_free(sched);
    free(line);
    printf("fin\n");
    return 0;
}