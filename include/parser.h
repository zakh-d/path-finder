#pragma once

#include "list.h"
#include "hashed_city.h"
#include "graph.h"
#include "custom_string.h"

struct city_t 
{
    String name;
    int x, y;
};

struct coord_t
{
    int x, y;
};

bool is_part_of_name(char c);
void parse_city_name(char* line, int x, int width, String& dest);
void parse_city(char** map, city_t* city, int width, int height);
void parse_flight(hash_node** hashmap, List<city_in_graph>* graph);