#include<stdio.h>
#include<stdlib.h>

int matrix[100][100]={0};
int path[100][100]={0};

int x,y;

typedef struct sll_node_s {
  struct sll_node_s *next;
  int col,row;
} *sll_node_t;

typedef struct sll_s {
  sll_node_t front;
  sll_node_t back;
  void (*fn)();  // Hàm giải phóng bộ nhớ cho nút
} *sll_t;

void sll_pop_front(sll_t list);
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

int check_neighbor(int a,int b){
    if(matrix[a-1][b]==0 ){
        x=a-1;
        y=b;
       return 1;
    }
    if(matrix[a+1][b]==0 ){   
        x=a+1;
        y=b;
       return 1;
    }
    if(matrix[a][b-1]==0 ){    
        x=a;
        y=b-1;
       return 1;
    }
    if(matrix[a][b+1]==0 ){
        x=a;
        y=b+1;
       return 1;   
    }
    return 0;
}

int main(){
    int m,n,r,c;
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
    sll_t queue=sll_create_list();
    sll_node_t nn=sll_create_node();
    nn->row=m;
    nn->col=n;
    matrix[m][n]=1;
    path[m][n]=1;
    sll_push_front(queue,nn);

    while(!sll_is_empty(queue)&&(queue->front->col<=c && queue->front->row<=r)){
        x=queue->front->row;
        y=queue->front->col;
        sll_pop_front(queue);
        if(check_neighbor(x,y)==1){
            matrix[x][y]=1;
            sll_node_t tmp=sll_create_node();
            tmp->row=x;
            tmp->col=y;
            path[x][y]=1;
            sll_push_back(queue,tmp);
        }       
    }
    for(int i=1;i<=6;i++){
        for(int j=1;j<=5;j++)
            printf("%d ",path[i][j]);
        printf("\n");
    }
    return 0;
}