#ifndef types_h
#define types_h

typedef struct hash hash;
typedef struct huff_heap huff_heap;
typedef struct huff_node huff_node;

struct huff_node
{
    int freq;
    void *item;
    unsigned short size;
    unsigned short binary;
    huff_node *left, *right;
};

struct hash
{
    huff_node *table[257];
};

struct huff_heap 
{
    int size;
    huff_node *data[257];
};

#endif