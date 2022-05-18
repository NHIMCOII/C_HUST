#include<stdio.h>
#include"cgen.ic"


void bn_pprint_node(bn_node_t n){
    printf("%p\n",n);
}

dll_t bn_get_leafs(bn_tree_t t){
    dll_t list =dll_create_list();
    bn_traverse_lnr(cur,t){
        if(cur->left==NULL&&cur->right==NULL){
            dll_push_back_g(list,(gtype){.v=cur});
        }
    }
    return list;
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
    dll_t leaf_list = dll_create_list();
    printf("\n");
    bn_pprint(t,bn_pprint_node);
    printf("\n");

    leaf_list=bn_get_leafs(t);
    dll_pprint_list(leaf_list);
    printf("\n");

    dll_traverse(cur,bn_get_leafs(t)){
        printf("%p->expected result\n   %p   \n\n",dll_node_g_value(cur).v,cur);
    }
    printf("\n");
    bn_free_tree(t);
    return 0;
}