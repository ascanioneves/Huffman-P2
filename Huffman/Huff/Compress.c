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

unsigned short compression(hash *new_hash, FILE *read_file, FILE *write_file)
{
    unsigned short binary, bit_count, aux, current_bits, mod;
    unsigned char byte, print_byte;
    while(feof(read_file) == 0)
    {
        print_byte = BYTE_ZERO; //começando o byte zerado
        bit_count = 0; //contador de bits
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
                    mod = current_bits % 8; //o quanto extrapolei, indica aonde vamos parar no proximo byte
                    if(current_bits < 16)
                    {
                        bit_count = mod; //será a quantidade de bits do proximo byte, por enquanto
                        binary >>= mod; //ignorando os bit que extrapolam no meu byte atual
                        print_byte |= binary; //setando
                        fprintf(write_file, "%c", print_byte);                       

                        print_byte = BYTE_ZERO; //zerando pois ja é o segundo byte
                        binary = aux; //pegando o mapeamento do char
                        binary <<= (16 - mod); //ignorando os bits ja usados no byte anterior
                        binary >>= 8; // reorganizando no byte da direita, de forma que os bits ja utilizados sao ignorados
                    }
                    else
                    {
                        binary >>= 8;
                        binary >>= mod;

                        print_byte |= binary;
                        fprintf(write_file, "%c", print_byte);
                         //apenas pra barra de progresso

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
    return 7 - bit_count; //não existe lixo com 8 bits 
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
    //colocando os 3 primeiros bits como o tamanho do lixo e os 5 ultimos como os 5 bits mais significativos do tree_size(mais a esquerda)
    //como o tamanho da arvore nunca ultrapassa 13, entao sempre os 3 primeiros bits serão 0;
    bytes[0] = trash_size << 5 | tree_size >> 8; 
    bytes[1] = tree_size; //pegando os 8 ultimos bytes que "sobraram", lembrar q ele faz o casting automaticamente
}

void compress(char *file_name)
{
    unsigned short tree_size = 0, trash_size;
    hash *new_hash = create_hash_table();
    FILE *file = fopen(file_name, "rb");
    new_hash = read(file_name, new_hash);
    huff_heap *new_heap = create_heap();

    for(int i = 0; i < 256; i++)
        if(new_hash -> table[i] != NULL)
            enqueue(new_heap, new_hash -> table[i]);

    huff_node *root = construct_tree(new_heap); 
    
    if(root == NULL)
        return;
    
    create_new_file_name(&file_name);
    new_map(root, 0, 0);
    FILE *write_file = fopen(file_name, "wb");
    fprintf(write_file, "%c%c", BYTE_ZERO, BYTE_ZERO); //para quando usar a rewind
    
    print_pre_order(root, write_file, &tree_size);
    trash_size = compression(new_hash, file, write_file);
    
    unsigned char bytes[2];

    construct_header(bytes, tree_size, trash_size);

    rewind(write_file);
    fprintf(write_file, "%c%c", bytes[0], bytes[1]); //escrevendo o cabeçalho
    fclose(write_file);
    printf("Arquivo comprimido com sucesso!\n\n");
}

