#include"C:\Users\PC\c_library\cgen\ext\io.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct sll_node_s {
  struct sll_node_s *next;
  double value;
} *sll_node_t;

typedef struct sll_s {
  sll_node_t front;
  sll_node_t back;
  void (*fn)();  // Hàm giải phóng bộ nhớ cho nút
} *sll_t;

int sll_is_empty(sll_t list);
void sll_pop_front(sll_t list);

sll_node_t sll_create_node() {
  sll_node_t n = malloc(sizeof(struct sll_node_s));
  n->next = NULL;
  return n;
}

void sll_free_node(sll_node_t node) {
  free(node);
}

sll_t sll_create_list() {
  sll_t list = malloc(sizeof(struct sll_s));
  list->front = NULL;
  list->back = NULL;
  list->fn = sll_free_node;
  return list;
}

void sll_free_list(sll_t list) {
  while (!sll_is_empty(list)) {
    sll_pop_front(list);
  }
  free(list);
}

void sll_push_front(sll_t list, sll_node_t node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
}

void sll_pop_front(sll_t list) {
  if (sll_is_empty(list)) {
    return;
  }
  sll_node_t tmp = list->front;
  list->front = list->front->next;
  if (list->front == NULL) {
    list->back = NULL;
  }
  if (list->fn) {
    list->fn(tmp);
  }
}

int sll_is_empty(sll_t list) {
  return list->front == NULL && list->back == NULL;
}

int main(){
    sll_t stack= sll_create_list();
    
    FILE *inp = fopen("inp.txt","r");
    char *line=NULL;
    char delin[]=" ";
    cgetline(&line,0,inp);
    char * ptr =strtok(line,delin);

    while(ptr!=NULL){
        double a= atof(ptr);
        sll_node_t nn=sll_create_node();
        nn->value=a;
        if(nn->value!=0){
            sll_push_front(stack,nn);
        }
    // plus
        if(strcmp(ptr,"+")==0){
            float result = stack->front->value;
            sll_pop_front(stack);
            result= result + stack->front->value;
            sll_pop_front(stack);
            nn->value=result;
            sll_push_front(stack,nn);
        }
    // minus
        if(strcmp(ptr,"-")==0){
            float result = stack->front->value;
            sll_pop_front(stack);
            result=  stack->front->value- result;
            sll_pop_front(stack);
            nn->value=result;
            sll_push_front(stack,nn);
        }
    //times    
        if(strcmp(ptr,"*")==0){
            float result = stack->front->value;
            sll_pop_front(stack);
            result= result * stack->front->value;
            sll_pop_front(stack);
            nn->value=result;
            sll_push_front(stack,nn);
        }    
    
        if(strcmp(ptr,"/")==0){
            float result = stack->front->value;
            sll_pop_front(stack);
            result=  stack->front->value/result;
            sll_pop_front(stack);
            nn->value=result;
            sll_push_front(stack,nn);
        }    
        ptr = strtok(NULL,delin);
    }
    fclose(inp);
    
    printf("Result = %.2f",stack->front->value);
    return 0;
}