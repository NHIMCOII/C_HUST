#include <stdio.h>
#include "cgen.ic"

bn_tree_t t;
sll_t list[100];

void bn_pprint_node(bn_node_t n)
{
    printf("%p\n", n);
}

sll_t *bn_layers(bn_tree_t t)
{
    gtype tmp;
    for (long i = 0; i <= bn_edge_height(t) ; i++)
    {
        bn_traverse_lrn(cur, t)
        {   
            tmp.v=cur;
            if(bn_distance(cur)==i)
                sll_push_back_g(list[i],tmp);          
        }
    }
}

int main()
{

    bn_node_t n1 = bn_create_node();
    bn_node_t n2 = bn_create_node();
    bn_node_t n3 = bn_create_node();
    bn_node_t n4 = bn_create_node();
    bn_node_t n5 = bn_create_node();
    bn_node_t n6 = bn_create_node();
    n1->left = n2;
    n2->top = n1;

    bn_connect2(n1, right, n3, top);
    bn_connect2(n2, left, n4, top);
    bn_connect2(n2, right, n5, top);
    bn_connect2(n3, right, n6, top);

    t = bn_create_tree(n1);
    for(long i=0;i<=bn_size(t)+1;i++){
        list[i] = sll_create_list();
    }
    bn_pprint(t,bn_pprint_node);
    // PRINT LIST
    bn_layers(t);
    for(long i=0;i<=bn_edge_height(t);i++){
        printf("STAGE %ld:  ",i);
        sll_traverse(cur,list[i]){
            printf("[%p]  ",sll_node_g_value(cur).v);
        }
        printf("\n");
    }

    bn_free_tree(t);
    return 0;
}