#include <stdio.h>
#include <stdlib.h>
// STRUCT DECLARE
typedef struct node_s
{
  struct node_s *left;
  struct node_s *right;
  int id;
} * node_t;

node_t r;

typedef struct stack_item_s
{
  node_t p;
  struct stack_item_s *next;
} * stack_item_t;

typedef struct stack_s
{
  stack_item_t top;
} * stack_t;

stack_t S;
//-------------------------------------------------------------------------------------
node_t create_node(int value)
{
  node_t newnode = malloc(sizeof(struct node_s));
  newnode->id = value;
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}
// RECURSIVE SOLUTION
void inOrder(node_t r)
{
  if (r == NULL)
    return;
  inOrder(r->left);
  printf("%d ", r->id);
  inOrder(r->right);
}

void preOrder(node_t r)
{
  if (r == NULL)
    return;
  printf("%d ", r->id);
  preOrder(r->left);
  preOrder(r->right);
}

void postOrder(node_t r)
{
  if (r == NULL)
    return;
  preOrder(r->left);
  preOrder(r->right);
  printf("%d ", r->id);
}

int count(node_t r)
{
  if (r == NULL)
    return 0;
  return 1 + count(r->left) + count(r->right);
}
// --------------------------------------------------------------------------
// STACK PROCEDURE

node_t stack_pop(stack_t S);
int stack_is_empty(stack_t S);

stack_item_t stack_create_item(node_t value)
{
  stack_item_t n = malloc(sizeof(struct stack_item_s));
  n->next = NULL;
  n->p = value;
  return n;
}

void stack_free_item(stack_item_t node)
{
  free(node);
}

stack_t stack_create()
{
  stack_t stack = malloc(sizeof(struct stack_s));
  stack->top = NULL;
  return stack;
}

void stack_free(stack_t stack)
{
  while (!stack_is_empty(stack))
  {
    stack_pop(stack);
  }
  free(stack);
}

void stack_push(stack_t stack, stack_item_t node)
{
  if (stack->top == NULL)
  {
    stack->top = node;
  }
  else
  {
    node->next = stack->top;
    stack->top = node;
  }
}

node_t stack_pop(stack_t stack)
{
  if (stack_is_empty(stack))
  {
    return NULL;
  }
  stack_item_t tmp = stack->top;
  node_t result = tmp->p;
  stack->top = stack->top->next;
  stack_free_item(tmp); 
  return result;
}

int stack_is_empty(stack_t stack)
{
  return stack->top == NULL;
}

node_t stack_peek(stack_t stack){
  if(stack_is_empty(S))
    return NULL;
  return stack->top->p;
}
// -------------------------------------------------------------------------------------------------
// ITERATIVE SOLUTION

void inOrder_iterative(node_t r)
{
  node_t tmp = r;
  stack_item_t curr = stack_create_item(tmp);
  int done = 0;

  while (!done)
  {
    if (curr->p != NULL)
    {
      stack_push(S, curr);
      tmp = tmp->left;
      curr = stack_create_item(tmp);
    }
    else
    {
      if (!stack_is_empty(S))
      {
        curr->p = stack_pop(S);
        printf("%d ", curr->p->id);
        curr->p = curr->p->right;
        tmp = curr->p;
      }
      else
        done = 1;
    }
  }
}

void preOrder_iterative(node_t r)
{
  if (r == NULL)
    return;
  node_t tmp = r;
  stack_item_t curr = stack_create_item(tmp);
  stack_push(S, curr);
  while (!stack_is_empty(S))
  {
    tmp = stack_pop(S);
    printf("%d ", tmp->id);

    if (tmp->right)
    {
      stack_item_t curr_r = stack_create_item(tmp->right);
      stack_push(S, curr_r);
    }
    if (tmp->left)
    {
      stack_item_t curr_l = stack_create_item(tmp->left);
      stack_push(S, curr_l);
    }
  }
}

void postOrder_iterative(node_t r)
{
  if (r == NULL)
    return;
  stack_item_t curr = stack_create_item(NULL);
  do
  {
    while (r)
    {
      if (r->right)
      {
        curr = stack_create_item(r->right);
        stack_push(S, curr);
      }
      curr=stack_create_item(r);
      stack_push(S, curr);
      r = r->left;
    }
    r = stack_pop(S);

    if (r->right && stack_peek(S) == r->right)
    {
      stack_pop(S);
      curr=stack_create_item(r);
      stack_push(S, curr);
      r = r->right;
    }

    else
    {
      printf("%d ", r->id);
      r = NULL;
    }
  } while (!stack_is_empty(S));
}
int main()
{
  r = create_node(10);
  node_t n1 = create_node(1);
  node_t n2 = create_node(2);
  node_t n5 = create_node(5);
  node_t n4 = create_node(4);
  node_t n7 = create_node(7);
  node_t n6 = create_node(6);
  node_t n8 = create_node(8);

  /*
                  10
               1       2
            5    6   4   7
                8
  */
  r->left = n1;
  r->right = n2;
  n1->left = n5;
  n2->left = n4;
  n2->right = n7;
  n1->right = n6;
  n6->left = n8;
  

  // r = create_node(15);
  // node_t n6 = create_node(6);
  // node_t n18 = create_node(18);
  // node_t n3 = create_node(3);
  // node_t n7 = create_node(7);
  // node_t n2 = create_node(2);
  // node_t n4 = create_node(4);
  // node_t n13 = create_node(13);
  // node_t n9 = create_node(9);
  // node_t n17 = create_node(17);
  // node_t n20 = create_node(20);

  // r->left=n6;
  // r->right=n18;
  // n6->left=n3;
  // n6->right=n7;
  // n3->left=n2;
  // n3->right=n4;
  // n7->right=n13;
  // n13->left=n9;
  // n18->left=n17;
  // n18->right=n20;

  S = stack_create();
  
  printf("\nRecursive_Solution:\n");
  
      inOrder(r);
  /*
      preOrder(r);
      printf("\n");
      printf("\n");
      postOrder(r);
  */
      printf("\n\nIterative_Solution\n");

  inOrder_iterative(r);
 /* 
  preOrder_iterative(r);
  printf("\n");
  printf("\n");
  postOrder_iterative(r);
*/
  stack_free(S);
  return 0;
}