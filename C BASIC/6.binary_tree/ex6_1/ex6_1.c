#include<stdio.h>
#include"cgen.ic"

void bn_pprint_node(bn_node_t n){
    printf("%p\n",n);
}

int main(){
    bn_node_t n1 = bn_create_node();
    bn_node_t n2 = bn_create_node();
    bn_node_t n3 = bn_create_node();
    bn_node_t n4 = bn_create_node();
    bn_node_t n5 = bn_create_node();
    bn_node_t n6 = bn_create_node();
    n1->left =n2;
    n2->top=n1;

    bn_connect2(n1,right,n3,top);
    bn_connect2(n2,left,n4,top);
    bn_connect2(n2,right,n5,top);
    bn_connect2(n3,right,n6,top);

    bn_tree_t t =bn_create_tree(n1);

    bn_pprint(t,bn_pprint_node);
    printf("Number of nodes: %ld\nEdge height: %ld",bn_size(t),bn_edge_height(t));
    bn_free_tree(&t);
    return 0;
}