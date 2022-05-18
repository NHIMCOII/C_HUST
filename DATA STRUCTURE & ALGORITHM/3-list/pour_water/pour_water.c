#include "cgen.ic"
#include <stdio.h>
#define MAX 10000
#include<stdlib.h>

sll_t Q,//queue
      S,//stack to save path
      L;//list to save pointer to dynamic memory
int visited[MAX][MAX]={0};

typedef struct _State_{
    int x,
        y;
    char* msg;//action to generate current state
    struct _State_ *p;//pointer to the state generating current state
}*State;

State target;
int a,b,c;

int reachTarget(State S){
    return S->x == c || S->y==c||S->x+S->y==c;
}

void markVisit(State S){
    visited[S->x][S->y]= 1;
}

void freeMemory(){
    sll_free_list(L);
}

int genMove1Out(State S){
    if(visited[0][S->y]) return 0;
    State newS;                                             //!!!!!!!!!!!
    newS->x=0;
    newS->y=S->y;
    newS->msg = "Do het nuoc o coc 1 ra ngoai\n";
    newS->p=S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMove2Out(State S){
    if(visited[S->x][0]) return 0;
    State newS;                                             //!!!!!!!!!!!
    newS->x=S->x;
    newS->y=0;
    newS->msg = "Do het nuoc o coc 2 ra ngoai\n";
    newS->p=S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMove1Full2(State S){
    if(S->x+S->y<b) return 0;
    if(visited[S->x + S->y - b][b]) return 0;
    State newS;
    newS->x= S->x + S->y - b;
    newS->y = b;
    newS->msg = "Do nuoc tu coc 1 vao day coc 2\n";
    newS->p= S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMove2Full1(State S){
    if(S->x+S->y<a) return 0;
    if(visited[a][S->x + S->y - a]) return 0;
    State newS;
    newS->x= a;
    newS->y = S->x + S->y - a;
    newS->msg = "Do nuoc tu coc 2 vao day coc 1\n";
    newS->p= S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMoveAll12(State S){
    if(S->x+S->y>b) return 0;
    if(visited[0][S->x + S->y]) return 0;
    State newS;
    newS->x= 0;
    newS->y = S->x + S->y ;
    newS->msg = "Do het nuoc tu coc 1 sang coc 2\n";
    newS->p= S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMoveAll21(State S){
    if(S->x+S->y>a) return 0;
    if(visited[S->x + S->y][0]) return 0;
    State newS;
    newS->x= S->x + S->y;
    newS->y = 0 ;
    newS->msg = "Do het nuoc tu coc 2 sang coc 1\n";
    newS->p= S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMoveFill1(State S){
    if(visited[a][S->y]) return 0;
    State newS;
    newS->x= a;
    newS->y = S->y ;
    newS->msg = "Do day nuoc vao coc 1\n";
    newS->p= S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

int genMoveFill2(State S){
    if(visited[S->x][b]) return 0;
    State newS;
    newS->x= S->x;
    newS->y = b;
    newS->msg = "Do day nuoc vao coc 2\n";
    newS->p= S;
    gtype tmp;
    tmp.v=newS;
    sll_push_back_g(Q,tmp);
    markVisit(newS);
    sll_push_back_g(L,tmp);
    if(reachTarget(newS)){
        target = newS;
        return 1;
    }
    return 0;
}

void print(State target){
    printf("-------------RESULT-------------\n");
    if(target==NULL)
        printf("Khong co loi giai!!!\n");
    State currentS=target;
    gtype tmp;
    tmp.v=currentS;
    while(currentS!=NULL){
        sll_push_front_g(S,tmp);
        currentS=currentS->p;
    }
    while(sll_length(S)>0){
        currentS=sll_pop_front_g(S).v;
        printf("%s,(%d,%d)\n",currentS->msg,currentS->x,currentS->y);
    }
}

void solve(){
    State S ;
    S->x=0; S->y=0; S->p=NULL;
    gtype tmp;
    tmp.v=S;
    sll_push_back_g(Q,tmp);
    markVisit(S);
    while(!sll_is_empty(Q)){
        State S = sll_pop_front_g(Q).v;
        sll_pop_front_g(Q);
        if(genMove1Out(S)) break;
        if(genMove2Out(S)) break;
        if(genMove1Full2(S)) break;
        if(genMoveAll12(S)) break;
        if(genMove2Full1(S)) break;
        if(genMoveAll21(S)) break;
        if(genMoveFill1(S)) break;
        if(genMoveFill2(S)) break;
    }
}

int main(){
    Q=sll_create_list();
    S=sll_create_list();
    L=sll_create_list();
    a=4;
    b=7;
    c=9;
    target=NULL;
    solve();
    print(target);
    freeMemory();
    return 0;
}
