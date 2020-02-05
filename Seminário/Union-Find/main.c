#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define maxN 500

int parent[maxN];

typedef struct adj adj;
typedef struct graph graph;

struct adj 
{
    int item;
    adj *next;
};
struct graph
{
    adj *vertices[maxN];
    bool visited[maxN];
};

adj* create_adj_list(int item)
{
    adj *new_adj_list = (adj *) malloc(sizeof(adj));
    new_adj_list -> item = item;
    new_adj_list -> next = NULL;
    return new_adj_list;
}

void add_edge(graph *new_graph, int vertex1, int vertex2)
{
    adj *vertex = create_adj_list(vertex2);
    vertex -> next = new_graph -> vertices[vertex1];
    new_graph -> vertices[vertex1] = vertex;
}

graph *create_graph()
{
    graph *new_graph = (graph *) malloc(sizeof(graph));
    
    int i;

    for(i = 0; i < maxN; i++)
    {
        new_graph -> visited[i] = false; 
        new_graph -> vertices[i] = NULL;
    }
    return new_graph;
}

int Find(int i)
{
    return parent[i] == i ? i : parent[i] = Find(parent[i]);
}


void Union(int x, int y)
{
    int xParent = Find(x);
    int yParent = Find(y);

    parent[xParent] = yParent;
}

void Initialize(int vertices)
{
    int i;

    for(i = 0; i < vertices; i++)
    {
        parent[i] = i;
    }
}

int main()
{
    int edges, vertices;
    scanf("%d%d", &edges, &vertices);
    graph *new_graph = create_graph();
    int i;
    for(i = 0; i < edges; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(new_graph, a, b);
        add_edge(new_graph, b, a);
        Union(a, b);
    }   

    return 0;
}
