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
    //Se sou pai retorne meu indice, se nao continue procurando ate achar o pai (parent[i] == -1)
    return parent[i] == -1 ? i : Find(parent[i]);
}

//Unindo um vertice a um subconjunto, consequentemente os dois subconjuntos
void Union(int x, int y)
{
    int xParent = Find(x);
    int yParent = Find(y);

    parent[xParent] = yParent;
}

bool has_cycle(graph *new_graph, int edges, int vertices)
{
    int i;
    //Percorrendo todos os vertices
    for(i = 0; i < vertices; i++)
    {
        adj *current_node = new_graph -> vertices[i];
        //Percorrendo a lista de adjacencia, verificando se o pai de x == y pois assim haverá ciclo, caso contrario nao havera
        while(current_node != NULL)
        {
            int x = Find(i);
            int y = Find(current_node -> item);

            if(x == y)
                return true;
            else
                Union(x, y);

            current_node = current_node -> next;
        }
    }
    return false;
}

int main()
{
    //Preenchenco o array de parent com -1
    memset(parent, -1, sizeof(parent));
    int edges, vertices;
    scanf("%d%d", &edges, &vertices);
    graph *new_graph = create_graph();
    int i;
    for(i = 0; i < edges; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(new_graph, a, b);
    }   
    printf("%s\n", has_cycle(new_graph, edges, vertices) ? "Yes" : "No");
    return 0;
}