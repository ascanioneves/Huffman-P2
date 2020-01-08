#ifndef decompress_h
#define decompress_h

//Função que cria a árvore de acordo com o pré ordem e usa um ponteiro para salvar a raiz da árvore.
void create_pre_order_tree(huff_node **tree, short int *count, FILE *file, short int tree_size);

//Função que retorna o bit da posição i do byte.
unsigned char current_bit(unsigned char byte, int i);

//Função que lê e descomprime o arquivo comprimido.
void descompression(huff_node *root, FILE *write_file, FILE *read_file, short int trash_size);

//Função que remove a extensão ".huff" do nome do arquivo comprimido.
void remove_huff(char **file_name);

//Função que verifica o cabeçalho e controla a descompressão, chamando outras as outras funções essenciais.
void descompress(char *file_name);

#endif