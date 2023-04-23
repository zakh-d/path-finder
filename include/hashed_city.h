#pragma once

#include "custom_string.h"

#define TABLE_SIZE 10003

struct hash_node {
    String key;
    int index;
};

hash_node** allocate_hash_table();
void free_hash_table(hash_node** table);
bool insert_into_hashmap(String& key, int index, hash_node** hashmap);