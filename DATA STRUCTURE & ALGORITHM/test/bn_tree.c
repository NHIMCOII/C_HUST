#include <stdio.h>
#include <stdlib.h>
// STRUCT DECLARE
typedef struct node_s
{
  struct node_s *left;
  struct node_s *right;
  int id;
} * node_t;

node_t r;

//-------------------------------------------------------------------------------------
node_t create_node(int value)
{
  node_t newnode = malloc(sizeof(struct node_s));
  newnode->id = value;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}
int cnt(node_t r){
  if(r==NULL)return 0;
  return 1+cnt(r->left)+cnt(r->right);
}

int main(){
    node_t n1=create_node(1);
    node_t n2=create_node(2);
    node_t n3=create_node(3);
    node_t n4=create_node(4);
    node_t n5=create_node(5);
    node_t n6=create_node(6);
    node_t n7=create_node(7);
    node_t n8=create_node(8);
    node_t n9=create_node(9);
    node_t n10=create_node(10);
    node_t n11=create_node(11);
    node_t n14=create_node(14);
    node_t n20=create_node(20);

    r=n20;
    n20->left=n2;
    n20->right=n6;
    n2->left=n7;
    n2->right=n1;
  n6->left=n3;
  n6->right=n5;
  n3->left=n8;
  n3->right=n9;
    printf("%d\n",cnt(r));
    printf("ye\n");
    return 0;
}