#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen.h"
#include"ext/io.h"

typedef struct _song_{
    char* name;
    char* artist;
    char* composer;
    int year;
}*song;
gdl_t list;

#define to_song(n) ((song)n)
#define to_song_name(n) (to_song(n)->name)
#define to_song_artist(n) (to_song(n)->artist)
#define to_song_composer(n) (to_song(n)->composer)
#define to_song_year(n) (to_song(n)->year)

void free_strdup(song I){
    free(to_song_name(I));
    free(to_song_artist(I));
    free(to_song_composer(I));
    free(I);
}

void free_inside_rbm(rbm_t t){
    rbm_traverse(k,v,t){
        free_strdup(to_song(v->v));
    }
}

int main(int argc ,char* argv[]){
    rbm_t t=rbm_create(gtype_cmp_s,NULL,NULL);
    FILE *fi=fopen(argv[1],"r");
    if(argc!=2){
        printf("Usage: ./prog inp.txt\n");
        exit(1);
    }
    char*line=NULL;
    while(cgetline(&line,0,fi)){
        song I=malloc(sizeof(struct _song_));
        tok_traverse(cur,line,"#*#"){
            I->name=strdup(cur);
            cur=strtok(NULL,"#*#");
            I->artist=strdup(cur);
            cur=strtok(NULL,"#*#");
            I->composer=strdup(cur);
            cur=strtok(NULL,"#*#");
            I->year=atoi(cur);
        }
        rbm_insert(t,gtype_s(I->name),gtype_v(I));
    }
    fclose(fi);
    printf("%ld\n\n",rbm_size(t));
    rbm_traverse(k,v,t){
        printf("%s %s %s %d\n",k->s,to_song_artist(v->v),to_song_composer(v->v),to_song_year(v->v));
    }
    //SEARCH VALUE THROUGH KEY
    gtype *tmp=rbm_value(t,gtype_s("Neon"));
    printf("\n\n%s %s %d\n",to_song_artist(tmp->v),to_song_composer(tmp->v),to_song_year(tmp->v));

    free_inside_rbm(t);
    rbm_free(t);
    free(line);
    printf("fin\n");
    return 0;
}