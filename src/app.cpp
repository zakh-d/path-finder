#include <iostream>
#include <cctype>
#include <cstring>
#include "list.h"
#include "vector.h"
#include "custom_string.h"
#include "graph.h"
#include "hashed_city.h"

struct coord_t
{
    int x, y;
};

struct city_t 
{
    String name;
    int x, y;
};

bool is_part_of_name(char c)
{
    if (c == '*' || c == '#' || c == '.')
        return false;
    return true;
}

void parse_city_name(char* line, int x, int width, String& dest)
{
    int l = x, r = x;

    while (l-1 >= 0 && r + 1 < width &&(is_part_of_name(line[l - 1]) || is_part_of_name(line[r + 1])))
    {
        if (is_part_of_name(line[l - 1])) l--;
        if (is_part_of_name(line[r + 1])) r++;
    }

    char tmp = line[r+1];
    line[r+1] = '\0';
    dest = &line[l];
    line[r+1] = tmp;
}

void parse_city(char** map, city_t* city, int width, int height)
{
    coord_t directions[8] = {
        {-1, 1}, {0, 1}, {1, 1},
        {-1, 0},         {1, 0},
        {-1, -1}, {0, -1}, {1, -1}
    };

    for (coord_t d: directions)
    {
        if (city->x + d.x < 0 || city->y + d.y < 0 || city->x + d.x >= width || city->y + d.y >= height)
            continue;
        
        if (is_part_of_name(map[city->y + d.y][city->x + d.x]))
        {
            parse_city_name(map[city->y + d.y], city->x + d.x, width, city->name);
            break;
        }
    }
}

void parse_flight(hash_node** hashmap, List<city_in_graph>* graph)
{
    std::cout << "start\n";
    String origin, dest;
    int distance;
    std::cin >> origin >> dest >> distance;
    std::cout << origin << " " << dest << " ";
    int index_origin = index_of_city(origin, hashmap);
    int index_dest = index_of_city(dest, hashmap);
    std::cout << index_origin << " " << index_dest << std::endl;
    if (index_origin == -1 || index_dest == -1) return;
    List<city_in_graph>& adjacency_list = graph[index_origin];
    bool found = false;
    for (Node<city_in_graph>* curr = adjacency_list.getHead(); curr != nullptr; curr = curr->next)
    {
        if (curr->data.index == index_dest)
        {
            if (curr->data.distance > distance)
            {
                curr->data.distance = distance;
            }
            found = true;
            break;
        }
    }

    if (!found)
    {
        adjacency_list.append({index_dest, distance});
    }
    std::cout << "finish\n";
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

    List<city_in_graph>* graph = allocate_adjacency_matrix(cities.getSize());
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

    
    free_adjacency_matrix(cities.getSize(), graph);
    free_hash_table(hashtable);

    return 0;
}