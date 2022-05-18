#include<stdio.h>
#include<stdlib.h>
typedef struct node_s{
    int id;
    struct node_s *leftMostChild;
    struct node_s *rightSibling;
}*node_t;

node_t root;

node_t create_node(int value){
    node_t newnode= malloc(sizeof(struct node_s));
    newnode->id=value;
    newnode->leftMostChild=NULL;
    newnode->rightSibling=NULL;
    return newnode;
}

void free_node(node_t node){
    free(node);
}

node_t find(node_t r,int v){
    if(r==NULL) return NULL;
    if(r->id == v) return r;
    node_t p = r->leftMostChild;// p==traverse
    while(p!=NULL){
        node_t h = find(p,v);
        if(h!=NULL) return h;// result breakpoint
        p = p->rightSibling;
    }
    return NULL;
}

int count(node_t r){
    if(r=NULL) return 0;
    int s=1;
    node_t p = r->leftMostChild;
    while(p!=NULL){
        s+= count(p);
        p=p->rightSibling;
    }
    return s;
}

int countLeaves(node_t r){
    if(r==NULL) return 0;
    int s=0;
    node_t p = r->leftMostChild;
    if(p==NULL) s=1;
    while(p!=NULL){
        s+=countLeaves(p);
        p=p->rightSibling;
    }
    return s;
}

int height(node_t p){
    if(p==NULL) return 0;
    int maxh = 0;
    node_t q = p->leftMostChild;
    while(q!=NULL){
        int h=height(q);
        if(h>maxh) 
            maxh = h ;
        q = q->rightSibling;
    }
    return maxh +1;
}

int depth(node_t r,int v,int d){
    //d la do sau cua nut r
    if(r=NULL) return -1;
    if(r->id == v) return d;
    node_t p = r->leftMostChild;
    while(p!=NULL){
        if(p->id==v) return d+1;
        int dv = depth(p,v,d+1);
        if(dv>0) return dv;
        p=p->rightSibling;
    }
    return -1;
}



int main(){
    root->id=0;
    node_t n1=create_node(1);
    node_t n2=create_node(2);
    node_t n3=create_node(3);
    node_t n4=create_node(4);
    node_t n5=create_node(5);

    root->leftMostChild=n1;
    n1->rightSibling=n2;
    n2->leftMostChild=n4;
    n2->rightSibling=n3;
    n4->rightSibling=n5;

    printf("%d \n",height(n1));
    return 0;
}