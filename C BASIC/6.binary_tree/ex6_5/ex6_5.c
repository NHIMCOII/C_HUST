#include <stdio.h>
#include "cgen.ic"
#include <string.h>
char buff[20][256];

int check(char test[256], int k){
    for (int i = 0; i < k; i++){
        if (strcmp(test, buff[i]) == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){

    if (argc != 2) {
          printf("Usage: ./bai6-5 input.txt \n");
    return 1;
    }
//create tree
    bn_tree_t t = bns_create_tree_g(NULL_PTR, gtype_cmp_s);
    int i = 0;
//read file 
    FILE *fi = fopen(argv[1], "r");
    while(fscanf(fi, "%s", buff[i] ) == 1){
         if (check(buff[i], i)) { 
            bns_insert_g(t, (gtype){.s = buff[i]});
        }
            i++;    
    }
    fclose(fi);

    bns_pprint(t, gtype_print_s);

    printf("So luong tu duy nhat: %d\n", bn_size(t));
    printf("Cac tu duy nhat:   ");
    bn_traverse_lnr(cur, t){
      printf("%s   ", bns_node_g_key(cur).s);
    };
    printf("\n\n\n");

    return 0;
}
