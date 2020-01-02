#ifndef heap_h
#define heap_h

#include "Types.h"

//Retorna 1 se a heap está vazia e 0 caso contrário.
int is_empty(huff_heap *heap); 

//Função que faz a troca de dois nós da heap, utilizando um nó auxiliar.
void swap(huff_heap *heap, int i, int j);

//Recebe um indice e retorna pai desse indice na heap.
int get_parent_index(huff_heap *heap, int i);

//Recebe um indice e retorna o filho a esquerda desse incide na heap.
int get_left_index(huff_heap *heap, int i);

//Recebe um indice e retorna o filho a direita desse indice na heap.
int get_right_index(huff_heap *heap, int i);

//Função que aloca o espaço para a heap, coloca o tamanho como 0 e preenche os nós como nulo.
huff_heap* create_heap();

//Função que controla e mantém as propriedades da min-heap, recebe a heap e um indice, e, a partir disso
//verifica se existe algum indice em que o pai tem a frequência maior que a dos filhos. Caso isso aconteça
//essa função irá corrigir e para manter a propriedade da min-heap.
void max_heapify(huff_heap *heap, int i);

//Função que insere um nó na heap, mantendo a propriedade da min-heap, se houver na inserção um caso em que
//o pai seja maior que o filho, essa função corrigirá, fazendo trocas até que a propriedade da min-heap seja
//restabelecida. Caso a a heap esteja vazia é exibida a mensagem de erro "Heap Overflow!" e a enqueue é encerrada.
void enqueue(huff_heap *heap, huff_node *node);

//Função que remove logicamente a raiz da heap e automaticamente restabelece a propriedade da min-heap caso 
//a mesma tenha sido cancelada. Caso a heap esteja vazia, a função retorna nulo como sinalizador de erro.
huff_node* dequeue(huff_heap *heap);


//Função para construir a árvore a partir da heap
huff_node* construct_tree(huff_heap *heap);

#endif