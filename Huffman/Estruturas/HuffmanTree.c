#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
//#include "HuffmanTree.h"

huff_node* create_node(unsigned char *element, huff_node *left, huff_node *right)
{
    huff_node *new_node = (huff_node *) malloc(sizeof(huff_node));
    new_node -> freq = 1;
    new_node -> item = (void *) element;
    new_node -> left = left;
    new_node -> right = right;
    new_node -> binary = 0; //todos bits ficam com 0
    new_node -> size = 0;
    return new_node;
}

huff_node* merge_nodes(huff_node *left, huff_node *right)
{
    huff_node *new_node = (huff_node *) malloc(sizeof(huff_node));
    new_node -> freq = (left -> freq) + (right -> freq);
    unsigned char *aux = (unsigned char *) malloc(sizeof(unsigned char));//tratando antes do casting
    *aux = '*';
    new_node -> item = (void *) aux;
    new_node -> left = left;
    new_node -> right = right;
    return new_node;
}

int is_leaf(huff_node *node) { return node -> left == NULL && node -> right == NULL; }

