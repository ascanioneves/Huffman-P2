#ifndef decompress_h
#define decompress_h

void create_pre_order_tree(huff_node **tree, short int *count, FILE *file, short int tree_size);

void descompress(char *file_name);

#endif