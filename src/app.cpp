#include <iostream>
#include <cctype>
#include <cstring>
#include "list.h"
#include "vector.h"
#include "custom_string.h"
#include "graph.h"
#include "hashed_city.h"
#include "parser.h"

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

void dfs_search_adjacency(int index, int width, int height, char** map, List<city_in_graph>* graph, Vector<city_t*>& cities)
{
    List<search_node> stack;
    coord_t directions[4] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    search_node start = {cities[index]->x, cities[index]->y, 0};
    int** visited = new int*[height];
    for (int i = 0; i < height; i++)
    {
        visited[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            visited[i][j] = 0;
        }
    }
    visited[start.y][start.x] = 1;
    stack.append(start);
    while ( stack.getSize() != 0)
    {
        search_node curr = stack.getTail()->data;
        stack.removeNode(stack.getTail());

        for (coord_t d: directions)
        {
            int nx = curr.x + d.x;
            int ny = curr.y +  d.y;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                if (visited[ny][nx]) continue;
                visited[ny][nx] = 1;
                if (map[ny][nx] == '#')
                {
                    stack.append({nx, ny, curr.distance + 1});
                }
                else if (map[ny][nx] == '*')
                {
                    int found_city_index = find_city_by_coords(nx, ny, width, cities);
                    insert_into_graph(index, found_city_index, curr.distance+1, graph);
                }
            }
        }
    }
    
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
    std::cout << "Total cities: " << cities.getSize() << std::endl;
    int counter = 0;

    hash_node** hashtable = allocate_hash_table();
    // for (Node<city_t*>* curr = cities.getHead(); curr != nullptr; curr = curr->next, i++)
    for (int i = 0; i < cities.getSize(); i++)
    {
        city = cities[i];
        parse_city(map, city, width, height);
        // std::cout << city->name << hash(city->name, 0) << std::endl;
        // std::cout << city->name.hash() << std::endl;
        int index = insert_into_hashmap(city->name, i, hashtable);
        dfs_search_adjacency(i, width, height, map, graph, cities);
        if (index >= 0)
        {
            counter++;

        }
    }

    std::cout << "Cities in hash table: " << counter << std::endl;

    int flightsCount;
    std::cin >> flightsCount;

    for (int i = 0; i < flightsCount; i++)
    {
        parse_flight(hashtable, graph);
    }

    // std::cout << "At pos (18, 2) " << cities[find_city_by_coords(18, 2, width, cities)]->name << std::endl;


    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
    }
    delete[] map;

    //for (Node<city_t*>* curr = cities.getHead(); curr != nullptr; curr = curr->next)
    for (int i = 0; i < cities.getSize(); i++)
    {
        delete cities[i];
    }

    
    free_adjacency_list(cities.getSize(), graph);
    free_hash_table(hashtable);

    return 0;
}