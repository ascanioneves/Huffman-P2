#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/HuffmanHash.h"
#include "../Estruturas/HuffmanHeap.h"
#include "../Estruturas/HuffmanTree.h"
#include "Compress.h"

#define BYTE_ZERO 0

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

hash* read(char *file_name, hash* hash, FILE *file)
{
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
    //fclose(file);
    return hash;
}

void new_map(huff_node *node, unsigned short count_size, unsigned short aux_binary, unsigned short *tree_size)
{
    if(node == NULL)
        return;
    else
    {
        *tree_size += 1;
        if(node -> left == NULL && node -> right == NULL)
        {
            node -> size = count_size;
            node -> binary = aux_binary;
        }
        new_map(node -> left, count_size + 1, aux_binary << 1, tree_size);
        new_map(node -> right, count_size + 1, (aux_binary << 1) + 1, tree_size);
    }
}

void print_pre_order(huff_node *node, FILE *write_file)
{
    if(node == NULL)
        return;
    else
    {
        if(*(unsigned char *) node -> item != '*') 
            fprintf(write_file, "%c - %hi\n", *(unsigned char *) node -> item, node -> size);
        print_pre_order(node -> left, write_file);
        print_pre_order(node -> right, write_file);
    }
}

unsigned short compression(hash *new_hash, FILE *file, FILE *write_file)
{
    unsigned short binary, bit_count, aux, current_bits, mod;
    unsigned char byte, print_byte;
    while(feof(file) == 0)
    {
        print_byte = BYTE_ZERO; //começando o byte zerado
        bit_count = 0; //contador de bits
        while(bit_count < 8)
        {
            if(fscanf(file, "%c", &byte) == EOF)
                break;
            else
            {
                printf("%c\n", byte);
                binary = new_hash -> table[byte] -> binary; 
                current_bits = bit_count + new_hash -> table[byte] -> size;
                if(current_bits > 8)
                {
                    aux = binary;
                    mod = current_bits % 8; //o quanto extrapolei, indica aonde vamos parar no proximo byte
                    if(current_bits < 16)
                    {
                        bit_count = mod; //será a quantidade de bits do proximo byte, por enquanto
                        binary >>= mod; //ignorando os bit que extrapolam no meu byte atual
                        print_byte |= binary; //setando
                        fprintf(write_file, "%c", print_byte);

                        print_byte = BYTE_ZERO; //zerando pois ja é o segundo byte
                        binary = aux; //pegando o mapeamento do char
                        binary <<= (16 - mod); //ignorando os bits ja usados
                        binary >>= 8; // reorganizando no byte da direita, de forma que os bits ja utilizados sao ignorados
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
                    binary <<= (8 - current_bits); //deslocando os bits para a posição correta(o maximo a esquerda) na hora de setar
                    bit_count += new_hash -> table[byte] -> size;
                }
                print_byte |= binary; //setando
            }
        }    
        fprintf(write_file, "%c", print_byte);
    }
    return 8 - bit_count == 8 ? 7 : 8 - bit_count; 
}

void compress(char *file_name)
{
    unsigned short tree_size = 0;
    hash *new_hash = create_hash_table();
    FILE *file = fopen(file_name, "rb");
    new_hash = read(file_name, new_hash, file);
    huff_heap *new_heap = create_heap();

    for(int i = 0; i < 256; i++)
        if(new_hash -> table[i] != NULL)
            enqueue(new_heap, new_hash -> table[i]);

    huff_node *root = construct_tree(new_heap);
    if(root == NULL)
        return;

    create_new_file_name(&file_name);
    new_map(root, 0, 0, &tree_size);
    FILE *write_file = fopen(file_name, "wb");
    fprintf(write_file, "%c%c", BYTE_ZERO, BYTE_ZERO);
    //fprintf(write_file,"Tree size %d\n", tree_size);
    //print_pre_order(root, write_file);
    unsigned short trash_size = compression(new_hash, file, write_file);
    fclose(file);
    fclose(write_file);
}

