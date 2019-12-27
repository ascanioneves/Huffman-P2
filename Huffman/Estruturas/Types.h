typedef struct huff_heap huff_heap;
typedef struct huff_node huff_node;

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