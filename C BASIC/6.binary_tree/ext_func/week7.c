#include"cgen.ic"
#include<stdio.h>
#include"C:\Users\PC\c_library\c-basic\baitap\baitap7.h"

bn_tree_t t;

void bn_pprint_node(bns_node_g_t n){
    printf("%ld\n",bns_node_g_key(n));
}

long bn_xdist(bn_tree_t t,bn_node_t n){
    long x=0,a=0;
    bn_traverse_lnr(cur,t){
        if(cur==n){
            while(cur!=t->root){
                if(cur->top->left==cur)
                    x--;
                if(cur->top->right==cur)
                    x++;
                cur=cur->top;
            }
            return x;
        }
    }
    return x;
}

int bn_is_bns(bn_tree_t t){
    long arr[100];
    int count=0;
    bn_traverse_lnr(cur,t){
        arr[count]=bns_node_g_key(cur).i;
        count++;
    }
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(arr[i]>arr[j])
                return 0;
        }
    }
    return 1;
}

bn_node_t bn_lca(bn_node_t n1, bn_node_t n2) {
    bn_node_t lca;
    if (n1->top == NULL || n2->top == NULL) {
        lca = NULL;
        return lca;
    }
    if (n1->top == n2->top)    {
        lca = n1->top;
        return lca;
    }
    if (bn_distance(n1) > bn_distance(n2)) {
        bn_lca(n1->top, n2);
    } else {
        bn_lca(n1, n2->top);
    }
}

bn_tree_t bns_parse_arri(int *a, size_t n){

}

int main(){
    int arr[]={1,2,3,5,6,8,9};
    t=bns_parse_arri(arr,7);
    bn_pprint(t,bn_pprint_node);
    printf("\n");
    bn_traverse_lnr(cur,t){
        printf("%ld  ",bns_node_g_key(cur).i);
    }
    return 0;
}