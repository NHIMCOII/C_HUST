#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

gvec_t vec;
int n;

int main(int argc,char* argv[]){
    FILE *fi=fopen(argv[1],"r");
    if(argc!=2){
        printf("Usage: ./prog collection.txt\n");
        exit(1);
    }
    fscanf(fi,"%d",&n);
    vec=gvec_create(n,NULL);
    int num;
    for(int i=0;i<n;i++){
        fscanf(fi,"%d",&num);
        rbm_t tree = rbm_create(gtype_cmp_s,NULL,NULL);
        for(int j=0;j<num;j++){
            char key[10];
            fscanf(fi,"%s",key);
            gtype *tmp = rbm_value(tree,gtype_s(key));
            if(!tmp)
                rbm_insert(tree,gtype_s(strdup(key)),gtype_l(1));
            else   {
                tmp->l++;
            }    
        }
        gvec_append(vec,gtype_v(tree));
    }
    fclose(fi);

    gvec_traverse(cur,vec){
        rbm_t tmp=cur->rbm;
        printf("%ld - ",rbm_size(tmp));
        rbm_traverse(k,v,tmp){
            printf("%s:%d  ",k->s,v->l);
        }
        printf("\n");
    }

    gvec_traverse(cur,vec){
        rbm_t tmp=cur->rbm;
        rbm_traverse(k,v,tmp){
            free(k->s);
        }
        rbm_free(tmp);
    }

    gvec_free(vec);

    printf("fin\n");
    return 0;
}