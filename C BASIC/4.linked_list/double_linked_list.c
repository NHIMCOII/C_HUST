#include <stdio.h>
#include <stdlib.h>

typedef struct dll_node_s
{
    struct dll_node_s *next;
    struct dll_node_s *prev;
    int value;
} * dll_node_t;

typedef struct dll_s
{
    dll_node_t front;
    dll_node_t back;
} * dll_t;

dll_node_t dll_create_node();
void dll_free_node(dll_node_t node);
dll_t dll_create_list();
void dll_free_list(dll_t list);

void dll_push_back(dll_t list, dll_node_t nn);
void dll_push_front(dll_t list, dll_node_t nn);
void dll_pop_back(dll_t list);
void dll_pop_front(dll_t list);
dll_node_t dll_front(dll_t list);
dll_node_t dll_back(dll_t list);
dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn);
dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn);
int dll_is_empty(dll_t list);
long dll_length(dll_t list);
dll_node_t dll_find(dll_t list, dll_node_t node);

// ----------------------------------------------------------------------------------------------

dll_node_t dll_create_node()
{
    dll_node_t n = malloc(sizeof(struct dll_node_s));
    n->next = n->prev = NULL;
    return n;
}

void dll_free_node(dll_node_t node)
{
    free(node);
}

dll_t dll_create_list()
{
    dll_t list = malloc(sizeof(struct dll_s));
    list->front = list->back = NULL;
    return list;
}

void dll_free_list(dll_t list)
{
    free(list->front);
    free(list->back);
}

void dll_push_back(dll_t list, dll_node_t node)
{
    if (list->back == NULL)
    {
        list->back = node;
        list->front = node;
    }
    else
    {
        node->prev = list->back;
        list->back->next = node;
        list->back = node;
    }
}

void dll_push_front(dll_t list, dll_node_t node)
{
    if (list->front == NULL)
    {
        list->back = node;
        list->front = node;
    }
    else
    {
        node->next = list->front;
        list->front->prev = node;
        list->front = node;
    }
}

void dll_pop_back(dll_t list)
{
    if (list->back == NULL)
        return;
    if (list->back->prev == NULL)
    {
        list->front = NULL;
        list->back = NULL;
        return;
    }

    dll_node_t tmp = list->back;
    list->back->prev->next = NULL;
    list->back = list->back->prev;
    dll_free_node(tmp);
}

void dll_pop_front(dll_t list)
{
    if (list->front == NULL)
        return;
    if (list->front->next == NULL)
    {
        list->front = NULL;
        list->back = NULL;
        return;
    }
    dll_node_t tmp = list->front;
    list->front->next->prev = NULL;
    list->front = list->front->next;
    dll_free_node(tmp);
}

dll_node_t dll_front(dll_t list)
{
    if(dll_is_empty(list)==1)
        return NULL;
    dll_node_t tmp = list->front;
    return tmp;
}

dll_node_t dll_back(dll_t list)
{
    if(dll_is_empty(list)==1)
        return NULL;
    dll_node_t tmp = list->back;
    return tmp;
}

dll_node_t dll_find(dll_t list, dll_node_t node)
{
    dll_node_t traversal = list->front;
    while (traversal != NULL)
    {
        if (traversal == node)
            return traversal;
        traversal = traversal->next;
    }
    return NULL;
}

dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn) {
  dll_node_t tmp=dll_find(list,pos);
  if(tmp==NULL)
    return nn;
  if (pos!=NULL) {
    dll_node_t tmp = pos->next;
    pos->next = nn;
    nn->prev = pos;
    nn->next = tmp;
    if (tmp!=NULL) {
      tmp->prev = nn;
    } else {
      list->back = nn;
    }
  } else {
    dll_push_back(list, nn);
  }
  return nn;
}


dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn) {
  dll_node_t tmp=dll_find(list,pos);
  if(tmp==NULL)
    return nn;
  if (pos!=NULL) {
    dll_node_t tmp = pos->prev;
    pos->prev = nn;
    nn->next = pos;
    nn->prev = tmp;
    if (tmp!=NULL) {
      tmp->next = nn;
    } else {
      list->front = nn;
    }
  } else {
    dll_push_front(list, nn);
  }
  return nn;
}
int dll_is_empty(dll_t list)
{
    if (list->front == NULL && list->back == NULL)
        return 1;
    else
        return 0;
}

long dll_length(dll_t list)
{
    long count = 0;
    if (dll_is_empty(list) == 1)
        return 0;
    dll_node_t traversal = list->front;
    while (traversal != NULL)
    {
        count++;
        traversal = traversal->next;
    }
    return count;
}

void dll_clear(dll_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
}

void dll_remove(dll_t list, dll_node_t node){
    if(node==NULL)
        return;
    if(list->back==list->front&&node==list->front){
        list->front=NULL;list->back=NULL;
        dll_free_node(node);
        return;
    }
    if(node==list->front){
        list->front=node->next;
        list->front->prev=NULL;
        dll_free_node(node);
        return;
    }
    if(node==list->back){
        list->back=node->prev;
        list->back->next=NULL;
        dll_free_node(node);
        return;
    }
    node->prev->next=node->next;
    node->next->prev=node->prev;
    dll_free_node(node);
    return;
}
int main()
{
    dll_t l = dll_create_list();
    dll_node_t n1 = dll_create_node(),
               n2 = dll_create_node(),
               n3 = dll_create_node(),
               n4 = dll_create_node(),
               n5 = dll_create_node();
    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    n4->value = 4;
    dll_node_t tmp = NULL;
    dll_push_back(l, n1);
    dll_push_back(l, n2);
    dll_push_back(l, n3);
    dll_inserta(l,n5, n4);
    dll_remove(l,n2);
    // dll_clear(l);
    dll_node_t traversal=l->front;
    while (traversal != NULL)
    {
        printf("%d ", traversal->value);
        traversal = traversal->next;
    }
    printf("\n");

    return 0;
}