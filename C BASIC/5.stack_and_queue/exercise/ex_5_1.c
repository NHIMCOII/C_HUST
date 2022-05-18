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

int dll_is_empty(list_t list);
void dll_pop_front(list_t list);

song_t dll_create_node() {
  song_t n = malloc(sizeof(struct song_s));
  n->next = n->prev = NULL;
  // n->name = n->path = NULL;
  return n;
}

void dll_free_node(song_t node) {
  free(node);
}

list_t dll_create_list() {
  list_t list =malloc(sizeof(struct list_s));
  list->front = list->back = NULL;
  list->fn = dll_free_node;
  return list;
}

void dll_free_list(list_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
  free(list);
}

void dll_push_back(list_t list, song_t nn) {
  if (list->back == NULL) {
    list->front = list->back = nn;
  } else {
    list->back->next = nn;
    nn->prev = list->back;
    list->back = nn;
  }
}

void dll_push_front(list_t list, song_t nn) {
  if (list->front == NULL) {
    list->front = list->back = nn;
  } else {
    list->front->prev = nn;
    nn->next = list->front;
    list->front = nn;
  }
}

void dll_pop_back(list_t list) {
  if (dll_is_empty(list)) {
    return;
  }
  song_t tmp = list->back;
  list->back = tmp->prev;
  if (list->back) {
    list->back->next = NULL;
  } else {
    list->front = NULL;
  }
  list->fn(tmp);
}

void dll_pop_front(list_t list) {
  if (dll_is_empty(list)) {
    return;
  }
  song_t tmp = list->front;
  list->front = tmp->next;
  if (list->front) {
    list->front->prev = NULL;
  } else {
    list->back = NULL;
  }
  list->fn(tmp);
}

song_t dll_front(list_t list) {
  return list->front;
}

song_t dll_back(list_t list) {
  return list->back;
}

/* insert nn after pos in list. push_back if pos == NULL */
song_t dll_inserta(list_t list, song_t pos, song_t nn) {
  if (!pos) {
    dll_push_back(list, nn);
    return nn;
  }

  song_t tmp = pos->next;
  pos->next = nn;
  nn->prev = pos;
  nn->next = tmp;
  if (tmp) {
    tmp->prev = nn;
  } else {
    list->back = nn;
  }
  return nn;
}

/* insert nn before pos in list. push_front is pos == NULL */
song_t dll_insertb(list_t list, song_t pos, song_t nn) {
  if (!pos) {
    dll_push_front(list, nn);
    return nn;
  }

  song_t tmp = pos->prev;
  pos->prev = nn;
  nn->next = pos;
  nn->prev = tmp;
  if (tmp) {
    tmp->next = nn;
  } else {
    list->front = nn;
  }
  return nn;
}

int dll_is_empty(list_t list) {
  return list->front == NULL && list->back == NULL;
}

long dll_length(list_t list) {
  long len = 0;
  song_t n = dll_front(list);
  while (n) {
    ++len;
    n = n->next;
  }
  return len;
}

void dll_erase(list_t list, song_t pos) {
  if (pos == list->front) {
    dll_pop_front(list);
    return;
  }
  if (pos == list->back) {
    dll_pop_back(list);
    return;
  }

  // front < pos < back
  song_t p1 = pos->prev,
             p2 = pos->next;
  p1->next = p2;
  p2->prev = p1;
  list->fn(pos);
}

void dll_clear(list_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
}

void dll_pprint_node(song_t node) {
  printf("[%s]", node->name);
}

static void _dll_pprint_list(list_t list, void (*ppn)()) {
  printf("NULL <= ");
  int first = 1;
  for (song_t cur = list->front; cur != NULL; cur = cur->next) {
    if (first) {
      first = 0;
    } else {
      printf(" <==> ");
    }
    ppn(cur);
  }
  printf(" => NULL\n");
}

void dll_pprint_list(list_t list) {
  _dll_pprint_list(list, dll_pprint_node);
}


int main(){
    list_t list=dll_create_list();
    char *token,*l;
    FILE *inp = fopen("songs.txt","r");
    char *line=NULL;   
    while(cgetline(&line,0,inp))  {
          l=strtok(line,"\n");
          while(l!=NULL){           
            token= strtok(l,"*#*");
        
            song_t new_song=dll_create_node();
            int count=1;
        
            while(token!=NULL){
              if(count%2!=0){
                  new_song->name=token;
              }
              else{
                  new_song->path=token;
              }
              token=strtok(NULL,"*#*"); 
              count++;            
            }
            dll_push_back(list,new_song);
            l=strtok(NULL,"\n");
          }       
    }
    fclose(inp);
    printf("%s\n",list->back->prev->path);
    return 0;
}
