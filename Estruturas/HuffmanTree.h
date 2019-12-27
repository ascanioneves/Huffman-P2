#ifndef tree_h
#define tree_h

#include "Types.h"

// função para criar um nó da hash com frequência 1.
extern huff_node* create_node(unsigned char *element); 

extern huff_node* merge_nodes(huff_node *left, huff_node *right);

#endif