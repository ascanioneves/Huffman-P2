#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
//#include "HuffmanTree.h"

huff_node* create_node(unsigned char *element)
{
    huff_node *new_node = (huff_node *) malloc(sizeof(huff_node));
    new_node -> freq = 1;
    new_node -> item = (void *) element;
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> bits = 0;
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

void print_pre_order(huff_node *node)
{   
    if(node == NULL)
        return;
    else
    {
        printf("%c - %d\n", *(unsigned char *) node -> item, node -> freq);
        print_pre_order(node -> left);
        print_pre_order(node -> right);
    }
}

