#include <iostream>
#include <cctype>
#include <cstring>
#include "list.h"
#include "vector.h"
#include "custom_string.h"
#include "graph.h"
#include "hashed_city.h"
#include "parser.h"
#include "priority_queue.h"

struct search_node {
    int x;
    int y;
    int distance;
};

int find_city_by_coords(int x, int y, int width_of_map, Vector<city_t*>& cities)
{
    int value = y * width_of_map + x;
    int start = 0, end = cities.getSize() - 1, middle;
    while (start <= end)
    {
        middle = (start + end) / 2;
        int middle_value = cities[middle]->y * width_of_map + cities[middle]->x;
        if (middle_value == value)
        {
            return middle;
        } else if (middle_value > value)
        {
            end = middle - 1;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}

void bfs_search_adjacency(int index, int width, int height, char** map, List<city_in_graph>* graph, Vector<city_t*>& cities, bool** visited)
{
    List<search_node> queue;
    coord_t directions[4] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    search_node start = {cities[index]->x, cities[index]->y, 0};

    if (visited[start.y][start.x])
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                visited[i][j] = false;
            }
        }
    }

    visited[start.y][start.x] = true;
    queue.append(start);
    while ( queue.getSize() != 0)
    {
        search_node curr = queue.getHead()->data;
        queue.removeNode(queue.getHead());

        for (coord_t d: directions)
        {
            int nx = curr.x + d.x;
            int ny = curr.y +  d.y;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                if (visited[ny][nx]) continue;
                visited[ny][nx] = true;
                if (map[ny][nx] == '#')
                {
                    queue.append({nx, ny, curr.distance + 1});
                }
                else if (map[ny][nx] == '*')
                {
                    int found_city_index = find_city_by_coords(nx, ny, width, cities);
                    insert_into_graph(index, found_city_index, curr.distance+1, graph);
                    insert_into_graph(found_city_index, index, curr.distance+1, graph);
                }
            }
        }
    }
}

int get_minimun(const Vector<int>& distances, const Vector<bool>& visited)
{
    int min = INT_MAX, min_index;

    for (int i = 0; i < distances.getSize(); i++)
    {
        if (distances[i] < min && !visited[i])
        {
            min = distances[i];
            min_index = i;
        }
    }

    return min_index;
}


struct way {
    int distance;
    Vector<int> path;
};


way dijkstra(int source, int dest, int n, List<city_in_graph>* graph)
{

    PriorityQueue pq(3*n);
    Vector<int> distances(n, INT_MAX);
    Vector<bool> visited(n, false);
    Vector<int> prev(n, -1);
    distances[source] = 0;
    pq.push(QueueNode(source, 0));
    while (pq.getSize())
    {
        int u = pq.pop().index;
        visited[u] = true;

        if (u == dest) break; // exit loop if destination is reached

        for (Node<city_in_graph>* curr = graph[u].getHead(); curr != nullptr; curr = curr->next)
        {
            int v = curr->data.index;
            int weight = curr->data.distance;

            if (!visited[v] && distances[u] != INT_MAX && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                pq.push(QueueNode(v, distances[v]));
                prev[v] = u; // keep track of previous node
            }
        }
    }

    Vector<int> path;
    int current = dest;
    while (current != -1)
    {
        path.push_back(current);
        current = prev[current];
    }
    path.reverse();
    way result;
    result.path = path;
    result.distance = distances[dest];
    return result;
}

int main()
{
    int width, height;
    std::cin >> width >> height;
    char **map = new char*[height];
    Vector<city_t*> cities;
    city_t* city;
    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];
        for (int j = 0; j < width; j++)
        {
            std::cin >> map[i][j];

            if (map[i][j] == '*')
            {
                city = new city_t;
                city->x = j;
                city->y = i;
                cities.push_back(city);
            }
        }
    }

    List<city_in_graph>* graph = allocate_adjacency_list(cities.getSize());

    hash_node** hashtable = allocate_hash_table();


    bool** visited = new bool*[height];
    for (int i = 0; i < height; i++)
    {
        visited[i] = new bool[width];
    }

    for (int i = 0; i < cities.getSize(); i++)
    {
        city = cities[i];
        parse_city(map, city, width, height);
        insert_into_hashmap(city->name, i, hashtable);
        bfs_search_adjacency(i, width, height, map, graph, cities, visited);
    }


    for (int i = 0; i < height; i++)
    {
        delete[] visited[i];
    }
    delete[] visited;

    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
    }
    delete[] map;


    int flightsCount;
    std::cin >> flightsCount;

    for (int i = 0; i < flightsCount; i++)
    {
        parse_flight(hashtable, graph);
    }

    // std::cout << "Graph filled\n";

    int connectionsCount;
    std::cin >> connectionsCount;
    for (int i = 0; i < connectionsCount; i++)
    {
        String origin, dest;
        int mode;
        std::cin >> origin >> dest >> mode;

        int index_origin = index_of_city(origin, hashtable);
        int index_dest = index_of_city(dest, hashtable);

        if (index_origin == -1 || index_dest == -1) {
            continue;
        }
        way solution = dijkstra(index_origin, index_dest, cities.getSize(), graph);
        if (mode == 0)
        {
            std::cout << solution.distance << std::endl;
        } else {

            std::cout << solution.distance;
            for (int j = 1; j < solution.path.getSize() - 1; j++)
            {
                std::cout << " " << cities[solution.path[j]]->name;
            }
            std::cout << std::endl;
        }
    }

    for (int i = 0; i < cities.getSize(); i++)
    {
        delete cities[i];
    }

    
    free_adjacency_list(cities.getSize(), graph);
    free_hash_table(hashtable);

    return 0;
}