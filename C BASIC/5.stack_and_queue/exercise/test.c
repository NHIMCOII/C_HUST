#include"C:\Users\PC\c_library\cgen\ext\io.h"
#include<stdio.h>
#include<string.h>
typedef struct song_s{
    char *name;
    char *path;
    struct song_s *next;
    struct song_s *prev;
}*song_t;

typedef struct list_s{
    song_t front;
    song_t back;
    void (*fn)();
}*list_t;
song_t dll_create_node() {
  song_t n = malloc(sizeof(struct song_s));
  n->next = n->prev = NULL;
  return n;
}

void dll_free_node(song_t node) {
  free(node);
}

list_t dll_create_list() {
  list_t list =malloc(sizeof(struct list_s));
  list->front = list->back = NULL;
  return list;
}
int main(){
    list_t list=dll_create_list();
    char *token,*l;
    FILE *inp = fopen("songs.txt","r");
    char *line=NULL;
    while(cgetline(&line,0,inp)){
        l=strtok(line,"\n");
        while(l!=NULL){
            printf("%s\n",l);
            l=strtok(NULL,"\n");
        }
    }
    fclose(inp);

    return 0;
}