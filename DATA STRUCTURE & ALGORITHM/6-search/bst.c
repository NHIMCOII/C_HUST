#include<stdio.h>
#include<stdlib.h>

typedef struct node_s{
    int key;
    struct node_s *left; 
    struct node_s *right; 
    struct node_s *parent; 
}*node_t;

node_t create_node(int value){
    node_t nn=NULL;
    nn=(node_t)malloc(sizeof(struct node_s));
    nn->key=value;
    nn->left=nn->right=nn->parent= NULL;
    return nn;
}

node_t findMin(node_t r){
    if(r==NULL)return NULL;
    else{
        if(r->left==NULL)return r;
        else return(findMin(r->left));
    }
}

node_t findMax(node_t r){
    if(r==NULL)return NULL;
    else{
        if(r->right==NULL)return r;
        else return(findMax(r->right));
    }
}

node_t predecessor(node_t r){
    if(r==NULL)return NULL;
    else if(r->left==NULL){
        if(r->parent->key>r->key)return predecessor(r->parent);
    }
    else{
        if(r->left->right==NULL) return r->left;
        else return(predecessor(r->left));
    }
}

int main(){
    node_t n1=create_node(1);
    node_t n2=create_node(2);
    node_t n3=create_node(3);
    node_t n4=create_node(4);
    node_t n5=create_node(5);

    n2->left=n1;
    n2->right=n4;
    n4->left=n3;
    n4->right=n5;

    n2->parent=NULL;
    n1->parent=n2;
    n3->parent=n4;
    n4->parent=n2;
    n5->parent=n4;

    printf("%d\n",predecessor(n3)->key);

    return 0;
}