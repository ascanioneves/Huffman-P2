typedef struct huff_heap huff_heap;
typedef struct huff_node huff_node;
typedef struct hash hash ;
typedef struct item item ;

struct huff_node
{
  int freq;
  void *item;
  huff_node *left, *right;
};
struct huff_heap 
{
  huff_node *data[257];
};

struct item 
{
    void *element ;
    unsigned int shift_bit ;
    int bits ;
    int frequencia ;
};
struct hash
{
    item *table[500] ;
};
