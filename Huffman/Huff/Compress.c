#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/HuffmanHash.h"
#include "../Estruturas/HuffmanHeap.h"
#include "../Estruturas/HuffmanTree.h"
#include "Compress.h"

unsigned char set_bit(unsigned char c, int i) 
{
    unsigned char mask = 1 << i;
    return mask | c;
}

hash* read(char *file_name, hash* hash)
{
    FILE *file = fopen(file_name, "rb");
    unsigned char *byte = (unsigned char *) malloc(sizeof(unsigned char));
    //colocando os caracteres com suas frequencias na hash
    while(1)
    {
        if(fscanf(file, "%c", byte) == EOF)
            break;
        else
            put_hash(hash, byte);
    }
    fclose(file);
    return hash;
}

void printar_hash(hash *hs)
{
    //printf("oi\n");
    for(int i = 0; i < 256; i++)
        if(hs -> table[i] != NULL && hs -> table[i] -> freq != 0) 
            printf("%c - %d\n", (char) i, hs -> table[i] -> freq);
}

void compress(char *file_name)
{
    hash *new_hash = create_hash_table();
    new_hash = read(file_name, new_hash);
    //printar_hash(new_hash);
    
}