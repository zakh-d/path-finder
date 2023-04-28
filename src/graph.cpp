#include "graph.h"

List<city_in_graph>* allocate_adjacency_list(int n)
{
    List<city_in_graph>* graph = new List<city_in_graph>[n];
    return graph;
}

void free_adjacency_list(int n, List<city_in_graph>* graph)
{
    delete[] graph;
}

void insert_into_graph(int index_origin, int index_dest, int distance, List<city_in_graph>* graph)
{
    if (index_origin == -1 || index_dest == -1) return;
    List<city_in_graph>& adjacency_list = graph[index_origin];
    adjacency_list.append({index_dest, distance});
    // bool found = false;
    // for (Node<city_in_graph>* curr = adjacency_list.getHead(); curr != nullptr; curr = curr->next)
    // {
    //     if (curr->data.index == index_dest)
    //     {
    //         if (curr->data.distance > distance)
    //         {
    //             curr->data.distance = distance;
    //         }
    //         found = true;
    //         break;
    //     }
    // }

    // if (!found)
    // {
    //     adjacency_list.append({index_dest, distance});
    // }
}