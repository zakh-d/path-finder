#include "parser.h"


bool is_part_of_name(char c)
{
    if (c == '*' || c == '#' || c == '.')
        return false;
    return true;
}

void parse_city_name(char* line, int x, int width, String& dest)
{
    int l = x, r = x;

    // while (l-1 >= 0 && r + 1 < width &&(is_part_of_name(line[l - 1]) || is_part_of_name(line[r + 1])))
    // {
    //     if (is_part_of_name(line[l - 1])) l--;
    //     if (is_part_of_name(line[r + 1])) r++;
    // }

    while (l-1 >= 0 && is_part_of_name(line[l-1]))
    {
        l--;
    }

    while (r+1 < width && is_part_of_name(line[r+1]))
    {
        r++;
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
    String origin, dest;
    int distance;
    std::cin >> origin >> dest >> distance;
    int index_origin = index_of_city(origin, hashmap);
    int index_dest = index_of_city(dest, hashmap);
    insert_into_graph(index_origin, index_dest, distance, graph);
}