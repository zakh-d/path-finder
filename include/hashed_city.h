#pragma once

#include "custom_string.h"

#define TABLE_SIZE 120011
#define MAX_OFFSET 40

struct hash_node {
    String key;
    int index;
};

int hash(String& key, int offset);
hash_node** allocate_hash_table();
void free_hash_table(hash_node** table);
int index_of_city(String& name, hash_node** hash_table);
int insert_into_hashmap(String& key, int index, hash_node** hashmap);