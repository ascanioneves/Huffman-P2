#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAXSIZE 20000

typedef struct avl_node avl_node;
typedef struct node node;

int data[MAXSIZE];
int data_random[MAXSIZE];

struct node
{
  int item;
  node *left;
  node *right;
};

struct avl_node
{
  int item;
  int h;
  avl_node* left;
  avl_node* right;
};

node *create_empty_binary_tree()
{
  return NULL;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int h(avl_node *node)
{
  if(node == NULL)
    return -1;
  else
    return 1 + max(h(node -> left), h(node -> right));
}

int is_balanced(avl_node *bt)
{
  int bf = h(bt -> left) - h(bt -> right);
  return ((-1 <= bf) && (bf <= 1));
}

int balance_factor(avl_node *bt)
{
  if(bt == NULL) 
    return 0;
  else if((bt -> left != NULL) && (bt -> right != NULL)) 
    return (bt -> left -> h - bt -> right -> h);
  else if((bt -> left != NULL) && (bt -> right == NULL)) 
    return (1 + bt -> left -> h);
  else 
    return (-bt -> right -> h - 1);  
}

node *create_binary_tree(int item, node *left, node *right)
{
  node *new_bt = (node *) malloc(sizeof(node));
  new_bt -> item = item;
  new_bt -> left = left;
  new_bt -> right = right;
  return new_bt;
}

avl_node *create_avl_tree(int item, avl_node *left, avl_node *right)
{
  avl_node *new_bt = (avl_node *) malloc(sizeof(avl_node));
  new_bt -> item = item;
  new_bt -> left = left;
  new_bt -> right = right;
  return new_bt;
}

avl_node* rotate_left(avl_node *bt)
{
  avl_node *subtree_root = NULL;

  if(bt != NULL && bt -> right != NULL)
  {
    subtree_root = bt -> right;
    bt -> right = subtree_root -> left;
    subtree_root -> left = bt;
  }
  subtree_root -> h = h(subtree_root);
  bt -> h = h(bt);
  return subtree_root;
}

avl_node* rotate_right(avl_node *bt)
{
  avl_node *subtree_root = NULL;

  if(bt != NULL && bt->left != NULL)
  {
    subtree_root = bt -> left;
    bt -> left = subtree_root -> right;
    subtree_root -> right = bt;
  }

  subtree_root -> h = h(subtree_root);
  bt -> h = h(bt);
  return subtree_root;
}

avl_node* add(avl_node *bt , int item)
{
  if (bt == NULL) return create_avl_tree(item, NULL, NULL);
  else if (bt -> item > item) bt -> left = add(bt -> left, item);
  else bt -> right = add(bt -> right, item);

  bt -> h = h(bt);
  avl_node *child;

  if(balance_factor(bt) == 2 || balance_factor(bt) == -2)
  {
    if(balance_factor(bt) == 2)
    {
      child = bt -> left;

      if(balance_factor(child) == -1)
        bt -> left = rotate_left(child);

      bt = rotate_right(bt);
    }
    else if (balance_factor(bt) == -2)
    {
      child = bt -> right;

      if(balance_factor(child) == 1)
        bt -> right = rotate_right(child);

      bt = rotate_left(bt);
    }
  }
  return bt;
}

void search(node *bt, int item, int *abbComparisons)
{
  *abbComparisons += 1;
  if(bt == NULL || bt -> item == item)
    return;
  else if(bt -> item > item)
    search(bt -> left, item, abbComparisons);
  else
    search(bt -> right, item, abbComparisons);
}

void search_avl(avl_node *node, int item, int *avlComparisons)
{
  *avlComparisons += 1;
  if(node == NULL || node -> item == item)
    return;
  else if(node -> item > item)
    search_avl(node -> left, item, avlComparisons);
  else
    search_avl(node -> right, item, avlComparisons); 
}

node *add_node(node *bt, int item)
{
  if(bt == NULL)
    bt = create_binary_tree(item, NULL, NULL);
  else if(bt -> item > item)
    bt -> left = add_node(bt -> left, item);
  else
    bt -> right = add_node(bt -> right, item);
  return bt;
}

void initialize_data()
{
  for(int i = 0; i < MAXSIZE; i++)
    data[i] = i, data_random[i] = rand() % MAXSIZE;
}

avl_node *create_empty_avl()
{
  return NULL;
}

int main()
{
  srand(time(NULL));
  initialize_data();
  node *root = create_empty_binary_tree();
  avl_node *avl_root = create_empty_avl();

  //Adicionando na ABB
  for(int i = 0; i < MAXSIZE; i++)
    root = add_node(root, data[i]);
  
  for(int i = 0; i < MAXSIZE; i++)
    avl_root = add(avl_root, data[i]);

  FILE *file = fopen("results.txt", "wb");
  fprintf(file, "value avl abb\n");
  for(long long i = 0; i < MAXSIZE; i++)
  {
    int avlComparisons = 0, abbComparisons = 0;
    int wanted = rand() % 1000;
    //int wanted = i;
    search(root, wanted, &abbComparisons);
    search_avl(avl_root, wanted, &avlComparisons);  
    fprintf(file, "%d %d %d\n", wanted, avlComparisons, abbComparisons);
  }
  fclose(file);
  //printf("Wanted = %d\nABB = %d\nAVL = %d\n", wanted, abbComparisons, avlComparisons);
  return 0;
}