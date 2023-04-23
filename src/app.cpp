#include <iostream>
#include <cctype>
#include <cstring>
#include "list.h"
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

int main()
{
    int width, height;
    std::cin >> width >> height;
    char **map = new char*[height];
    List<city_t*> cities;
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
                cities.append(city);
            }
        }
    }

    int* matrix = allocate_adjacency_matrix(cities.getSize());
    std::cout << "Total cities: " << cities.getSize() << std::endl;
    int counter = 0;

    hash_node** hashtable = allocate_hash_table();
    int i = 0;
    for (Node<city_t*>* curr = cities.getHead(); curr != nullptr; curr = curr->next, i++)
    {
        city = curr->data;
        parse_city(map, city, width, height);
        if (insert_into_hashmap(city->name, i, hashtable))
        {
            counter++;
        }
    }

    std::cout << "Cities in hash table: " << counter << std::endl;

    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
    }
    delete[] map;
    delete[] matrix;

    free_hash_table(hashtable);


    return 0;
}