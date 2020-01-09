#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estruturas/HuffmanHash.h"
#include "../Estruturas/HuffmanHeap.h"
#include "../Estruturas/HuffmanTree.h"
#include "Compress.h"
#include "Decompress.h"

void start()
{
    printf("\n\n\n");
    printf("---------------------------------------------\n");
    printf("|                 HUFFMAN                   |\n");
    printf("|                                           |\n");
    printf("|             Desenvolvido por:             |\n");
    printf("|                                           |\n");
    printf("|             Ascanio Savio                 |\n");
    printf("|             Danilo Vasconcelos            |\n");
    printf("|             Gabriel Souza                 |\n");
    printf("|             Joao Ayalla                   |\n");
    printf("|             Jorge Firmo                   |\n");
    printf("---------------------------------------------\n");
    printf("\n\n\n");
}
int main()
{
    start();

    while(1)
    {
        printf("Qual sera a operacao ?\n");
        printf("Digite '1' para compressao\n");
        printf("Digite '2' para descompressao\n");
        printf("Digite '3' para sair\n");
        printf("\n\n\n");
        int op;
        char file[1000];

        scanf("%d", &op);

        if(op == 1)
        {
            printf("Digite o diretorio do arquivo a ser comprimido:\n");
            scanf(" %[^\n]s", file);
            printf("O arquivo: %s sera comprimido agora\n\n", file);
            compress(file);
        }
        else if(op == 2)
        {
            printf("Digite o diretorio do arquivo a ser descomprimido:\n");
            scanf(" %[^\n]s", file);
            printf("O arquivo: %s sera descomprimido agora\n\n", file);
            decompress(file);
        }
        else if(op == 3)
        {
            printf("Encerrando...\n");
            return 0;
        }
        else 
        {
            printf("Operacao Invalida\n\n");
            continue;
        }
    }
    

}