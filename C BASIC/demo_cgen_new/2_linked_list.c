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

gtype create_song_g(char* name,char* artist,char* composer,int year){
    song nn=malloc(sizeof(struct _song_));
    nn->name=strdup(name);
    nn->artist=strdup(artist);
    nn->composer=strdup(composer);
    nn->year=year;
    return (gtype){.v=(void *)nn};
}

void free_song_g(gtype g){
    song tmp=g.v;
    free(tmp->name);
    free(tmp->artist);
    free(tmp->composer);
    free(g.v);
}

void gdl_delete_node(gdl_t list,gtype *pos){
    if(pos == list->front){
        gdl_pop_front(list);
        return;
    }
    else if(pos== list->back){
        gdl_pop_back(list);
        return;
    }
    else if(gdn_next(pos)==NULL&&gdn_prev(pos)==NULL){
        free(pos);
        list->back=list->front=NULL;
        return;
    }
    else{
        gdl_traverse(cur,list){
            if(pos==cur){
                gdn_next(gdn_prev(pos))=gdn_next(pos);
                gdn_prev(gdn_next(pos))=gdn_prev(pos);
            }
        }
        free(pos);
    }
}

int main(int argc,char* argv[]) {
    list=gdl_create(free_song_g);
    FILE *fi=fopen(argv[1],"r");
    if(argc!=2){
        printf("Usage: ./prog inp.txt\n");
        exit(1);
    }
    char*line=NULL;
    while(cgetline(&line,0,fi)){
        struct _song_ I;
        tok_traverse(cur,line,"#*#"){
            I.name=cur;
            cur=strtok(NULL,"#*#");
            I.artist=cur;
            cur=strtok(NULL,"#*#");
            I.composer=cur;
            cur=strtok(NULL,"#*#");
            I.year=atoi(cur);
        }
        gdl_push_back(list,create_song_g(I.name,I.artist,I.composer,I.year));
    }
    fclose(fi);
    gtype *g;
    g=gdn_next(gdl_front(list));
    // PRINT NODE VALUE
    // song pos=(song)gdn_value(g).v;  
    // printf("%s\n",pos->name);
    gdl_inserta(list,g,create_song_g("new song","new artist","new composer",2022));
    gdl_delete_node(list,g);
    gdl_traverse(cur,list){
        song s=(song)(gdn_value(cur).v);
        printf("%s %s %s %d\n",s->name,s->artist,s->composer,s->year);
    }
    while(!gdl_is_empty(list)){
        song s= gdl_back(list)->v;
        if(strcmp(s->name,"new song")==0)
            printf("%s\n",s->composer);
        gdl_pop_back(list);
    }
    // if(gdl_is_empty(list)) 
    //     printf("ALL CLEAR\n");
    gdl_free(list);
    free(line);
    return 0;
}