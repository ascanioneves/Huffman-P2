#ifndef compress_h
#define compress_h

//Função que cria um novo arquivo com o nome do arquivo a ser comprimido juntamente com a extensão ".huff".
void create_file_name(char **file_name);

//Função que lê o arquivo a ser comprimido e insere o bytes com suas respectivas frequências na hash.
hash* read(char *file_name, hash *hash);

//Função que gera o arquivo comprimido.
unsigned short compression(hash *new_hash, FILE *read_file, FILE *write_file);

//Função que printa a árvore em pré ordem e calcula o tamanho da mesma.
void print_pre_order(huff_node *node, FILE *write_file, unsigned short *tree_size);

//Função que constroi o cabeçalho.
void construct_header(unsigned char *bytes, unsigned short tree_size, unsigned short trash_size);

//Função que controla o processo de compressão, chamando todas as outras funções essenciais.
void compress(char *file_name);

//Retorna o numero total de bytes do arquivo comprimido
int get_total_bytes();

#endif