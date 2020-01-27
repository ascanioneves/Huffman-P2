#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"
#include "Types.h"

int is_empty(huff_heap *heap)
{
    return (heap -> size == 0);
}

void swap(huff_heap *heap, int i, int j)
{
    huff_node *aux = heap -> data[i];
    heap->data[i] = heap -> data[j];
    heap->data[j] = aux;
}

int get_parent_index(huff_heap *heap, int i) { return i >> 1; }

int get_left_index(huff_heap *heap, int i) { return i << 1; }

int get_right_index(huff_heap *heap, int i) { return (i << 1) + 1; }

huff_heap* create_heap()
{
    huff_heap *new_heap = (huff_heap *) malloc(sizeof(huff_heap));
    new_heap -> size = 0;
    int i;
    for(i = 1; i < 257; i++)
      new_heap -> data[i] = NULL;
    return new_heap;
}

void min_heapify(huff_heap *heap, int i, int size)
{
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);
    if(left_index <= size && heap->data[left_index]->freq <= heap->data[i]->freq)
        largest = left_index;
    else
        largest = i;
    
    if(right_index <= size && heap->data[right_index]->freq <= heap->data[largest]->freq)
        largest = right_index;
    if(heap->data[i]->freq != heap->data[largest]->freq)
    {
        swap(heap, i, largest);
        min_heapify(heap, largest, size);
    }
}

void enqueue(huff_heap *heap, huff_node *node)
{
    if(heap -> size >= 256)
    {
        printf("Heap Overflow!\n");
        return;
    }
    else
    {
        heap->data[++heap->size] = node;
        int key_index = heap->size;
        int parent_index = get_parent_index(heap, key_index);
        while(parent_index >= 1 && heap->data[key_index]->freq <= heap->data[parent_index]->freq)
        {
            swap(heap, key_index, parent_index);
            key_index = parent_index;
            parent_index = get_parent_index(heap, key_index);
        }
    } 
}

huff_node* dequeue(huff_heap *heap)
{ 
    if(is_empty(heap))
    {
        printf("Heap Underflow!\n");
        return NULL;
    }
    else
    {
        huff_node *aux = heap -> data[1];
        heap -> data[1] = heap -> data[heap -> size--];
        min_heapify(heap, 1, heap -> size);
        return aux;
    }
}

huff_node* construct_tree(huff_heap *heap)
{
    while(heap -> size > 1)
    {
        huff_node *aux1 = dequeue(heap);
        huff_node *aux2 = dequeue(heap);
        huff_node *parent_node = merge_nodes(aux1, aux2);
        enqueue(heap, parent_node);
    }
    return heap -> data[1];
}


