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
hmap_t map;

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

void free_inside_hmap(hmap_t map){
    hmap_traverse(k,v,map){
        free_strdup(to_song(v->v));
    }
}

int main(int argc,char* argv[]) {
    map=hmap_create(gtype_hash_s,gtype_cmp_s,NULL,NULL);
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
        hmap_insert(map,gtype_s(I->name),gtype_v(I));
    }
    fclose(fi);


    gvec_t tmp=gvec_create(0,gtype_free_v);
    hmap_traverse(key,value,map){
        if(to_song_year(value->v)>2010)
            gvec_append(tmp,gtype_v(to_song(key)));
        printf("%s %s %s %d\n",key->s,to_song_artist(value->v),to_song_composer(value->v),to_song_year(value->v));
    }
    printf("\n\n");

    gvec_traverse(cur,tmp){
        hmap_remove(map,gtype_s(to_song_name(cur->v)));
    }

    hmap_traverse(key,value,map){
        printf("%s %s %s %d\n",key->s,to_song_artist(value->v),to_song_composer(value->v),to_song_year(value->v));
    }

    free_inside_hmap(map);
    hmap_free(map);
    gvec_free(tmp);
    printf("fin\n");
    return 0;
}