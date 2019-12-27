#ifndef hash_h
#define hash_h
#include "Types.h"

// função para criar a hash.
hash* create_hash_table(); 

// Função que incrementa a frequência caso o nó já exista, caso contrário chama a create_node().
void put_hash(hash *ht , unsigned char *element);

#endif
