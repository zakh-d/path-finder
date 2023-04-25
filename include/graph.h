#pragma once
#include "list.h"

struct city_in_graph {
    int index;
    int distance;
};

List<city_in_graph>* allocate_adjacency_list(int n);
void free_adjacency_list(int n, List<city_in_graph>* graph);