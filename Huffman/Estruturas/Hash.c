#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "Hash.h"
#include "types.h"

hash *create_hash_table ()
{
    hash *new_hash = (hash*) malloc(sizeof(hash)) ;

    int i;

    for (i = 0 ; i < 257 ; i++) 
    {
        new_hash -> table[i] -> element = NULL ;
        new_hash -> table[i] -> shift_bit = 0 ;
        new_hash -> table[i] -> bits = 0 ;
    }

    return new_hash ;
}

hash_node *set_data (hash_node *head , void *element , unsigned int shift_bit , int bits)
{
	head -> element = element ;
	head -> shift_bit = shift_bit ;
	head -> bits = bits ;

	return head ;
}

void put (hash *ht , void *element , unsigned int shift_bit , int bits)
{
	int i;
	int aux = *(int*)element ;
	i = aux % 257 ; 

	ht -> table[i] = set_data(ht -> table[i] , element , shift_bit , bits) ;
}



