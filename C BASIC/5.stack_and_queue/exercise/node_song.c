#include"C:\Users\PC\c_library\cgen\sll.h"
#include"C:\Users\PC\c_library\cgen\dll.h"
#include<stdlib.h>
#include<stdio.h>

typedef struct dll_node_song_s{
    struct dll_node_s base;
    char *name;
    char *path;
}*dll_node_song_t;

#define to_dll_node_song(n)((dll_node_song_t)n)

#define dll_node_song_name(n)(to_dll_node_song(n)->name)
#define dll_node_song_path(n)(to_dll_node_song(n)->path)


dll_node_t dll_create_node_song(const char *name,const char* path){
    dll_node_t tmp=dll_create_node();
    dll_node_song_t nn = realloc(tmp,sizeof(struct dll_node_s));
    nn->name=strdup(name);
    nn->path=strdup(path);
    return (to_dll)nn;
}

void dll_free_node_song(dll_node_t n){
    dll_node_song_t tmp = to_dll_node_song(n);
    free(tmp->name);
    free(tmp->path);
}

dll_t dll_create_list_song(){
    dll_t tmp=dll_create_list();
    tmp->fn = dll_free_node_song;
    return list;
}

void dll_push_back_song(dll_t list,const char* name,const char *path){
    dll_push_back(list,dll_create_node_song(name,path));
}

void dll_pprint_node_song(dll_node_t node){
    printf("[%s]",dll_node_song_name(node));
}

void dll_pprint_list_song(dll_t list){
    dll_traverse(cur,list){
        dll_pprint_node_song(cur);
        printf("\n");
    }
}

dll_node_t dll_node_by_id(dll_t lít,long id){
    long len=dll_length(list);
    if(id<1||id>len){
        return NULL;
    }
    dll_node_t cur =list->front;
    for(int i=1;i<id;i++){
        cur=cur->next;
    }
    return cur;
}

int main(){
    dll_t list = dll-dll_create_list_song();
    dll_push_back_song(list,"Chiec la thu phai","/home/nva/music/chiec-la-thu-phai.mp3");

    dll_pprint_list_song(list);
}