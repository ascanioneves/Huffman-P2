#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/HuffmanHash.h"
#include "../Estruturas/HuffmanHeap.h"
#include "../Estruturas/HuffmanTree.h"
#include "Compress.h"
#include "Descompress.h"

#define BYTE_ZERO 0

void create_new_file_name(char **file_name)
{
    unsigned short size_1 = strlen(*file_name), size_2 = size_1 + 5;
    char *new_file_name = (char *) calloc(size_2, sizeof(char));
    strcpy(new_file_name, *file_name);
    strcat(new_file_name, ".huff");
    *file_name = new_file_name;
}

hash* read(char *file_name, hash* hash)
{
    FILE *file = fopen(file_name, "rb");
    unsigned char *byte = (unsigned char *) malloc(sizeof(unsigned char));
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

unsigned short compression(hash *new_hash, FILE *read_file, FILE *write_file)
{
    unsigned short binary, bit_count, aux, current_bits, mod;
    unsigned char byte, print_byte;
    while(feof(read_file) == 0)
    {
        print_byte = BYTE_ZERO;
        bit_count = 0;
        while(bit_count < 8)
        {
            if(fscanf(read_file, "%c", &byte) == EOF)
                break;
            else
            {
                binary = new_hash -> table[byte] -> binary; 
                current_bits = bit_count + new_hash -> table[byte] -> size;
                if(current_bits > 8)
                {
                    aux = binary;
                    mod = current_bits % 8;
                    if(current_bits < 16)
                    {
                        bit_count = mod;
                        binary >>= mod; 
                        print_byte |= binary; 
                        fprintf(write_file, "%c", print_byte);                       

                        print_byte = BYTE_ZERO; 
                        binary = aux;
                        binary <<= (16 - mod);
                        binary >>= 8;
                    }
                    else
                    {
                        binary >>= 8;
                        binary >>= mod;

                        print_byte |= binary;
                        fprintf(write_file, "%c", print_byte);

                        print_byte = BYTE_ZERO;
                        binary = aux;
                        binary <<= (16 - (new_hash -> table[byte] -> size - (8 - bit_count)));
                        binary >>= 8;

                        print_byte |= binary;
                        fprintf(write_file, "%c", print_byte);
                        

                        print_byte = BYTE_ZERO;
                        binary = aux;
                        binary <<= (16 - mod);
                        binary >>= 8;
                        bit_count = mod;
                    }
                }
                else
                {
                    binary <<= (8 - current_bits);
                    bit_count += new_hash -> table[byte] -> size;
                }
                print_byte |= binary;
            }
        }    
        fprintf(write_file, "%c", print_byte);
        
    }
    return 7 - bit_count;
}

void print_pre_order(huff_node *node, FILE *write_file, unsigned short *tree_size)
{
    if(node == NULL)
        return;
    else
    {
        *tree_size += 1;
        if(is_leaf(node))
        {
            if(* (unsigned char *) node -> item == '*' || *(unsigned char *) node -> item == '\\')
            {
                fprintf(write_file, "\\");
                *tree_size += 1;
            }
        }
        fprintf(write_file, "%c", * (unsigned char *) node -> item);
        print_pre_order(node -> left, write_file, tree_size);
        print_pre_order(node -> right, write_file, tree_size);
    }
}

void construct_header(unsigned char *bytes, unsigned short tree_size, unsigned short trash_size)
{
    bytes[0] = trash_size << 5 | tree_size >> 8; 
    bytes[1] = tree_size;
}

void compress(char *file_name)
{
    unsigned short tree_size = 0, trash_size;
    hash *new_hash = create_hash_table();
    FILE *file = fopen(file_name, "rb");
    new_hash = read(file_name, new_hash);
    huff_heap *new_heap = create_heap();

    int file_char = 0;
    for(int i = 0; i < 256; i++)
        if(new_hash -> table[i] != NULL)
            enqueue(new_heap, new_hash -> table[i]);
   

    huff_node *root = construct_tree(new_heap); 
    
    if(root == NULL)
        return;
    
    create_new_file_name(&file_name);
    new_map(root, 0, 0);
    FILE *write_file = fopen(file_name, "wb");
    fprintf(write_file, "%c%c", BYTE_ZERO, BYTE_ZERO);
    
    print_pre_order(root, write_file, &tree_size);
    trash_size = compression(new_hash, file, write_file);
    
    unsigned char bytes[2];

    construct_header(bytes, tree_size, trash_size);

    rewind(write_file);
    fprintf(write_file, "%c%c", bytes[0], bytes[1]);
    fclose(write_file);
    printf("Arquivo comprimido com sucesso!\n\n");
}

