#include<stdio.h>
#include<string.h>
#include"C:\Users\PC\c_library\cgen\cgen.h"
#include"C:\Users\PC\c_library\cgen\ext\io.h"

struct word_tf{
    char* word;
    long tf;
};

#define TF(p) (())

int word_tf_inc_cmp(cpnst void *p1,const void *p2){

}
int main(){

    FILE *inp=fopen("lisa_all_text.txt","r");
    char *line=NULL;
    rbm_t words = rbm_create(gtype_cmp_s);
    while(cgetline(&line,0,inp)){
        remove_tail_lf(line);
        char*tok = strtok(line," ");
        while(tok){
            printf("%s\n",tok);
            rbm_node_t n=rbm_insert(words,gtype_s(strdup(tok)),gtype_i(-1));
            if(n->value.i==-1){
                n->value.i=1;
            }else{
                n->value.i+=1;
            }
            tok= strtok(NULL," ");
        }
    }
    fclose(inp);
    free(line);
    long sz = bn_size((bn_tree_t)words);
    printf("So luong tu duy nhat = %ld\n",sz);
    long idx=0;
    rbm_traverse(cur,words){
        a[idx].word= cur
    }
    
    return 0;
}