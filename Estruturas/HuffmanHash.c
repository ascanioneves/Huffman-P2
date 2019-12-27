#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "HuffmanTree.h"
#include "Types.h"

hash *create_hash_table()
{
    hash *new_hash = (hash *) malloc(sizeof(hash)) ;

    for(int i = 0; i < 256; i++) 
    {
        new_hash -> table[i] = NULL;
    }

    return new_hash;
}

void put_hash(hash *ht , unsigned char *element)
{
    if(ht -> table[*element] == NULL)
    {
        huff_node *new_node = create_node(element);
        ht -> table[*element] = new_node;
    }
    else
        ht -> table[*element] -> freq++;
}



