#ifndef hash_h
#define hash_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "Types.h"

hash *create_hash_table () ; // função para criar a hash 

hash_node *set_data (hash_node *head , void *element , unsigned int shift_bit , int bits) ; 
// função para atribuir os dados na hash

void put (hash *ht , void *element , unsigned int shift_bit , int bits) ;
// função para inserir na hash, usando a função set_data para atribuir os dados

#endif
