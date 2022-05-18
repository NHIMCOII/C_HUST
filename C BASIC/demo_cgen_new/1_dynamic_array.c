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

gvec_t vec;
#define vec(val) ((song)(((gtype*)val)->v))
int gtype_qsort(const void* a,const void*b){
    return strcmp(vec(a)->artist,vec(b)->artist);
}

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

void free_inside_gvec(gvec_t v){
    gvec_traverse(cur,v){
        free_strdup(to_song(cur->v));
    }
}


int main(int argc,char* argv[]) {
  vec = gvec_create(1, NULL);
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
        gvec_append(vec,gtype_v(I));
    }
    fclose(fi);

    printf("Number of songs: %ld\n",gvec_size(vec));
    gvec_qsort(vec,gtype_qsort);
    gvec_traverse(value,vec){
        printf("%-20s %-20s %-10s %-5d\n",to_song_name(value->v),to_song_artist(value->v),to_song_composer(value->v),to_song_year(value->v));
    }
    // gvec_arr return pointer
    song tmp = (song)gvec_elem(vec,1).v;
    printf("%s\n",tmp->artist);
    printf("%s\n",tmp->name);
    // printf("%ld\n",gvec_elem_idx(vec,&gvec_elem(vec,1)));
    gvec_remove(vec,1);
    gvec_traverse(value,vec){
        song tmp=value->v;
        printf("%-20s %-20s %-10s %-5d\n",to_song_name(value->v),to_song_artist(value->v),to_song_composer(value->v),to_song_year(value->v));
    }
    // gvec_set_capacity(vec,20);
    printf("gvec capacity:%ld\ngvec size: %ld\n",gvec_capacity(vec),gvec_size(vec));
    free_inside_gvec(vec);
    gvec_free(vec);
  free(line);
  printf("fin\n");
  return 0;
}