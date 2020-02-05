#include <stdio.h>
#include <stdlib.h>
#include "../Estruturas/Types.h"
#include "../Estruturas/HuffmanHeap.h"
#include "../Estruturas/HuffmanTree.h"
#include "../Estruturas/HuffmanHash.h"
#include "CUnit/CUnit.h"

huff_heap *heap = NULL;
huff_node *root = NULL;

const char tree[7] = "*A**DCB";

int init_suite()
{
  return 0;
}

int clean_suite()
{
  return 0;
}

void get_tree_size(huff_node *node, unsigned short *i)
{
  if(node == NULL)
    return;
  else
  {
    if(is_leaf(node))
      if(node -> item == '*' || node -> item == '\\')
        *i += 1;
    *i += 1;
    get_tree_size(node -> left, i);
    get_tree_size(node -> right, i);
  }
}

void tree_compare(huff_node *node, unsigned short *i)
{
  if(node == NULL)
    return;
  else
  {
    if(is_leaf(node))
      CU_ASSERT_EQUAL(tree[(*i)], node -> item);
    *i += 1;
    tree_compare(node -> left, i);
    tree_compare(node -> right, i);
  }
}

void testing_create_heap()
{
  heap = create_heap();
  CU_ASSERT_NOT_EQUAL(NULL, heap);
  CU_ASSERT(0 == heap -> size);
}

void run_tree(huff_node *node)
{
  if(node == NULL)
    return;
  else
  {
    if(node -> item == 'A')
      CU_ASSERT_EQUAL(0, node -> binary);
    if(node -> item == 'B')
      CU_ASSERT_EQUAL(3, node -> binary);
    if(node -> item == 'C')
      CU_ASSERT_EQUAL(5, node -> binary);
    if(node -> item == 'D')
      CU_ASSERT_EQUAL(4, node ->binary);
    run_tree(node -> left);
    run_tree(node -> right);
  }
}

void testing_newmap()
{
  new_map(root, 0, 0);
  run_tree(root);
}

void testing_tree_build()
{
  huff_node *nodeA = create_node('A', NULL, NULL);
  nodeA -> freq = 4;
  huff_node *nodeB = create_node('B', NULL, NULL);
  nodeB -> freq = 3;
  huff_node *nodeC = create_node('C', NULL, NULL);
  nodeC -> freq = 2;
  huff_node *nodeD = create_node('D', NULL, NULL);
  nodeD -> freq = 1;
  enqueue(heap, nodeA);
  enqueue(heap, nodeB);
  enqueue(heap, nodeC);
  enqueue(heap, nodeD);
  root = construct_tree(heap);
  unsigned short i = 0;
  tree_compare(root, &i);
  CU_ASSERT_EQUAL(strlen(tree), i);
  i = 0;
  get_tree_size(root, &i);
  CU_ASSERT_EQUAL(strlen(tree), i);
}

void testing_hash()
{
  hash *new_hash = create_hash_table();
  CU_ASSERT_NOT_EQUAL(new_hash, NULL);
  CU_ASSERT_PTR_NULL(new_hash->table[0]);
  unsigned char *ch = (unsigned char*)malloc(sizeof(unsigned char));
  *ch = (unsigned char)'a';
  put_hash(new_hash, ch);
  put_hash(new_hash, ch);
  CU_ASSERT_PTR_NOT_NULL(new_hash->table['a']);
  CU_ASSERT_EQUAL(new_hash->table['a']->freq, 2);
}

void testing_enqueue()
{
  heap = create_heap();
  huff_node *node = create_node('P', NULL, NULL);
  enqueue(heap, node);
  CU_ASSERT_NOT_EQUAL(NULL, heap -> data[1]);
  CU_ASSERT(node == heap -> data[1]);
  CU_ASSERT(node -> item == heap -> data[1] -> item);
  CU_ASSERT(node -> freq == heap -> data[1] -> freq);
  CU_ASSERT(1 == heap -> size);
  CU_ASSERT(NULL == heap -> data[1] -> left);
  CU_ASSERT(NULL == heap -> data[1] -> right);
  ++heap -> data[1] -> freq; 
  huff_node *next_node = create_node('K', NULL, NULL);
  enqueue(heap, next_node);
  CU_ASSERT_NOT_EQUAL(NULL, heap -> data[1]);
  CU_ASSERT(next_node == heap -> data[1]);
  CU_ASSERT(next_node -> item == heap -> data[1] -> item);
  CU_ASSERT(next_node -> freq == heap -> data[1] -> freq);
  CU_ASSERT_EQUAL(2, heap -> size);
}

void testing_dequeue()
{
  huff_node *dequeued = heap -> data[1];
  CU_ASSERT_EQUAL(dequeued, dequeue(heap));
  dequeued = heap -> data[1];
  CU_ASSERT_EQUAL(dequeued, dequeue(heap));
  CU_ASSERT_PTR_NULL(dequeue(heap)); 
}

int main()
{
  CU_pSuite pSuite = NULL;

  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  
  pSuite = CU_add_suite("TesteSuite1", init_suite, clean_suite);

  if(pSuite == NULL)
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(NULL == CU_add_test(pSuite, "\n\n Testing CreateHeap Function \n\n", testing_create_heap))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if(NULL == CU_add_test(pSuite, "\n\n Testing Enqueue Function \n\n", testing_enqueue))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if(NULL == CU_add_test(pSuite, "\n\n Testing Dequeue Function \n\n", testing_dequeue))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if(NULL == CU_add_test(pSuite, "\n\n Testing TreeBuild Function \n\n", testing_tree_build))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if(NULL == CU_add_test(pSuite, "\n\n Testing NewMap Function \n\n", testing_newmap))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }
  if(NULL == CU_add_test(pSuite, "\n\n Testing Hash \n\n", testing_hash))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
