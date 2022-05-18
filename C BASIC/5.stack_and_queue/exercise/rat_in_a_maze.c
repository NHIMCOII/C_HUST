#include<stdio.h>
#include<stdlib.h>

int matrix[100][100]={0};
int r,c;//matrix's size
typedef struct{
    int x,y;
}cord;

typedef struct sll_node_s {
  struct sll_node_s *next;
  int row,col;
} *sll_node_t;

typedef struct sll_s {
  sll_node_t front;
  sll_node_t back;
  void (*fn)();  // Hàm giải phóng bộ nhớ cho nút
} *sll_t;

sll_t queue;
sll_t stack;
cord sll_pop_front(sll_t list);
int sll_is_empty(sll_t list);

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

void sll_push_back(sll_t list, sll_node_t node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
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

cord sll_pop_front(sll_t list) {
  cord t;
  if (sll_is_empty(list)) {
    return ;
  }
  sll_node_t tmp = list->front;
  t.x=list->front->row;
  t.y=list->front->col;
  list->front = list->front->next;
  if (list->front == NULL) {
    list->back = NULL;
  }
  if (list->fn) {
    list->fn(tmp);
  }
  return t;
}

int sll_is_empty(sll_t list) {
  return list->front == NULL && list->back == NULL;
}

void sll_delete_node(sll_t list,sll_node_t node){

}

void check_neighbor(cord t){//tren duoi trai phai   
    if(matrix[t.x-1][t.y]==0 ){
        sll_node_t tmp=sll_create_node();
        cord ti=t;
        ti.x=ti.x-1;
        tmp->row=ti.x;
        tmp->col=ti.y;
        sll_push_back(queue,tmp);
    }
    if(matrix[t.x+1][t.y]==0 ){  
        sll_node_t tmp=sll_create_node();
        cord ti=t;
        ti.x=ti.x+1;
        tmp->row=ti.x;
        tmp->col=ti.y; 
        sll_push_back(queue,tmp);
    }
    if(matrix[t.x][t.y-1]==0 ){    
        sll_node_t tmp=sll_create_node();
        cord ti=t;
        ti.y=ti.y-1;
        tmp->row=ti.x;
        tmp->col=ti.y;   
        sll_push_back(queue,tmp);
    }
    if(matrix[t.x][t.y+1]==0 ){
        sll_node_t tmp=sll_create_node();
        cord ti=t;
        ti.y=ti.y+1;
        tmp->row=ti.x;
        tmp->col=ti.y;
        sll_push_back(queue,tmp);
    } 
}

void BFS(){
    while(!sll_is_empty(queue)&&(queue->front->row<=r&&queue->front->col<=c)){
        cord t;
        t = sll_pop_front(queue);
        matrix[t.x][t.y]=1;
        check_neighbor(t);
    }
}


int main(){
    int m,n;
    queue=sll_create_list();
    stack=sll_create_list();
    FILE *inp=fopen("matrix.txt","r");
    // read matrix's info
    fscanf(inp,"%d%d",&r,&c);
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            fscanf(inp,"%d",&matrix[i][j]);
    // 
    fclose(inp);
    printf("Enter start point : ");
    scanf("%d%d",&m,&n);
    if(matrix[m][n]==1)
      printf("\nError start point, already filled.\nPlease try again!\n\n");
    // Initial queue
    sll_node_t nn=sll_create_node();
    //
    nn->row=m;
    nn->col=n;
    sll_push_back(queue,nn);
    BFS();
    /*printf("(Finish)");
    sll_node_t traverse=stack->front;
    while(traverse!=NULL){
       printf("<-(%d;%d)",traverse->row,traverse->col);
       traverse=traverse->next;
    }*/

    for(int i=1;i<=6;i++){
      for(int j=1;j<=5;j++)
        printf("%d ",matrix[i][j]);
      printf("\n");
    }
    
    return 0;
}