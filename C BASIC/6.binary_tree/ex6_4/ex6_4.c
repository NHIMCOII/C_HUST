#include<stdio.h>
#include"cgen.ic"

bn_tree_t t;

void bn_pprint_node(bn_node_t n){
    printf("%p\n",n);
}

gtype *bns_keys(bn_tree_t t){
  long sz = bn_size(t);
  if (sz > 0 ){
    printf("Cac khoa tang dan:");
    bn_traverse_lnr(cur, t){
      printf(" %ld    ", bns_node_g_key(cur).i);
    };
  }
}

int main() {
  t = bns_create_tree_g(NULL, gtype_cmp_i);
  bns_insert_g(t, gtype_i(40));
  bns_insert_g(t, gtype_i(10));
  bns_insert_g(t, gtype_i(40));
  bns_insert_g(t, gtype_i(50));
  bns_insert_g(t, gtype_i(20));
  bns_insert_g(t, gtype_i(60));
  bns_pprint(t, gtype_print_i);
  bns_keys(t);
  return 0;
}