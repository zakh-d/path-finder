#include "graph.h"

List<city_in_graph>* allocate_adjacency_matrix(int n)
{
    List<city_in_graph>* graph = new List<city_in_graph>[n];
    return graph;
}

void free_adjacency_matrix(int n, List<city_in_graph>* graph)
{
    delete[] graph;
}