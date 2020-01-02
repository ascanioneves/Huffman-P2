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

void create_new_file_name(char **file_name)
{
    unsigned short size_1 = strlen(*file_name), size_2 = size_1 + 5;
    char *new_file_name = (char *) calloc(size_2, sizeof(char));
    strcpy(new_file_name, *file_name);
    strcat(new_file_name, ".huff");
    *file_name = new_file_name; // file_name = nome_arquivo.huff
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
        {
            if(hash -> table[*byte] == NULL) 
            {
                unsigned char *aux = (unsigned char *) malloc(sizeof(unsigned char));
                *aux = *byte;
                put_hash(hash, aux);
            }
            else
                put_hash(hash, byte);
        }
    }
    fclose(file);
    return hash;
}

void new_map(huff_node *node, unsigned short count_size, unsigned short aux_binary, int *tree_size)
{
    *tree_size += 1;
    if(node == NULL)
        return;
    else
    {
        if(node -> left == NULL && node -> right == NULL)
        {
            node -> size = count_size;
            node -> binary = aux_binary;
        }
        new_map(node -> left, count_size + 1, aux_binary << 1, tree_size);
        new_map(node -> right, count_size + 1, (aux_binary << 1) + 1, tree_size);
    }
}

void compress(char *file_name)
{
    int tree_size = 0;
    hash *new_hash = create_hash_table();
    new_hash = read(file_name, new_hash);
    huff_heap *new_heap = create_heap();

    for(int i = 0; i < 256; i++)
        if(new_hash -> table[i] != NULL)
            enqueue(new_heap, new_hash -> table[i]);

    huff_node *root = construct_tree(new_heap);

    if(root == NULL)
        return;

    create_new_file_name(&file_name);
    FILE *write_file = fopen(file_name, "wb");
    fprintf(write_file, "%c%c", 0, 0);
    new_map(root, 0, 0, &tree_size);
    print_pre_order(root, write_file);
    fclose(write_file);

    
}

