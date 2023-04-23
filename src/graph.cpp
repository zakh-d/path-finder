#include "graph.h"

int* allocate_adjacency_matrix(int n)
{
    int size = n/2*(n-1);

    return new int[size];
}

int index_in_matrix(int index1, int index2, int n)
{
    if (index1 == index2 || index1 < 0 || index1 >= n || index2 < 0 || index2 >= n)
    {
        return -1;
    }
    int smaller = (index1 < index2) ? index1 : index2;
    int bigger = index1 + index2 - smaller;

    int index = (n - 1 + n - smaller) / 2 * smaller + bigger - smaller - 1;
    return index;
}