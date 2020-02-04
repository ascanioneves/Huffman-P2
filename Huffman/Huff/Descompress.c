#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/HuffmanHash.h"
#include "../Estruturas/HuffmanHeap.h"
#include "../Estruturas/HuffmanTree.h"
#include "Descompress.h"
#include "Compress.h"

void create_pre_order_tree(huff_node **tree, short int *count, FILE *file, short int tree_size)
{
    //percorremos a arvore inteira
    if(*count == tree_size)
        return;
    else
    {
        unsigned char byte;
        if(fscanf(file, "%c", &byte) == EOF)
        {
            printf("Algo de errado com o cabecalho\n");
            return;
        }  
        unsigned char *aux_byte = (unsigned char *) malloc(sizeof(unsigned char));
        *aux_byte = byte;

        *count += 1;

        //nao sou folha
        if(byte == '*')
        {
            *tree = create_node(aux_byte, NULL, NULL);
            create_pre_order_tree(&((*tree) -> left), count, file, tree_size);
            create_pre_order_tree(&((*tree) -> right), count, file, tree_size);
        }
        //sou uma folha e me encaixo no caso especial do '\\'
        else if(byte == '\\')
        {
            if(fscanf(file, "%c", &byte) == EOF)
            {
                printf("Arvore invalida\n");
                return;
            }  
            *aux_byte = byte;
            *count += 1;
            *tree = create_node(aux_byte, NULL, NULL); 
        }
        //sou uma folha e nao me encaixo no caso especial
        else
            *tree = create_node(aux_byte, NULL, NULL);
    }
}

unsigned char current_bit(unsigned char byte, int i)
{
    unsigned char mask = 1 << (7 - i);
    return mask & byte;
}

void descompression(huff_node *root, FILE *write_file, FILE *read_file, short int trash_size)
{
    unsigned short i = 0, bit;
    unsigned char byte, byte_2;
    huff_node *current_node = root;
    if(feof(read_file))
        printf("Arquivo incompleto\n");
    else
    {
        while(fscanf(read_file, "%c", &byte) != EOF)
        {
            int i = 0;
            //estou no ultimo byte
            if(fscanf(read_file, "%c", &byte_2) == EOF)
            {
                while(i < (8 - trash_size))
                {
                    unsigned short bit = (unsigned short) current_bit(byte, i);
                    if(current_node -> right != NULL || current_node -> left != NULL)
                    {
                        if(bit)
                            current_node = current_node -> right;
                        else 
                            current_node = current_node -> left;
                        i++;
                    }
                    if(is_leaf(current_node))
                    {
                        fprintf(write_file, "%c", *(unsigned char *) current_node -> item);
                        current_node = root;
                    }
                }
                return;
            }
            else
            {
                //caso que nao é o ultimo byte
                while(i < 8)
                {
                    unsigned short bit = (unsigned short) current_bit(byte, i);
                    if(current_node -> right != NULL || current_node -> left != NULL)
                    {
                        if(bit)
                            current_node = current_node -> right;
                        else 
                            current_node = current_node -> left;
                        i++;
                    }
                    if(is_leaf(current_node))
                    {
                        fprintf(write_file, "%c", *(unsigned char *) current_node -> item);
                        current_node = root;
                    }
                }
                fseek(read_file, -1, SEEK_CUR); //volta o ponteiro do arquivo 1 vez por causa dos 2 fscanf
            }
        }
    }
}

void remove_huff(char **file_name)
{
    short size = strlen(*file_name);
    char *new_name = (char *) calloc(size - 5, sizeof(char));
    for(int i = 0; i < size - 5; i++)
        new_name[i] = (*file_name)[i];

    *file_name = new_name;
}

void descompress(char *file_name)
{
    short int count = 0;
    unsigned short tree_size, trash_size;
    unsigned char byte, aux_byte;

    huff_node *tree = NULL;

    FILE *read_file = fopen(file_name, "rb");

    if(fscanf(read_file, "%c", &byte) == EOF)
    {
        printf("Cabecalho invalido\n");
        return;
    }

    aux_byte = byte;
    trash_size = (unsigned short) byte >> 5; //tamanho do lixo, jogando os 3 primeiros bits pro final

    tree_size = (unsigned short) ((byte << 3) >> 3); //ignorando o lixo, que ja foi guardado
    tree_size <<= 8; //voltando pro primeiro byte

    if(fscanf(read_file, "%c", &byte) == EOF)
    {
        printf("Cabecalho invalido\n");
        return;
    }

    tree_size |= (unsigned short) byte; //setando o que falta que está no segundo byte do cabeçalho

    create_pre_order_tree(&tree, &count, read_file, tree_size);
    remove_huff(&file_name);

    FILE *write_file = fopen(file_name, "wb");
    descompression(tree, write_file, read_file, trash_size);
    printf("Arquivo descomprimido com sucesso!\n\n");
    fclose(read_file);
    fclose(write_file);
}