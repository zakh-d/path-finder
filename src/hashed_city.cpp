#include "hashed_city.h"


int hash(String& key, int offset)
{
    const int c1 = 5, c2 = 23;
    long long value = key.hash();
    value += offset * c1 + offset*offset * c2;
    return value % TABLE_SIZE;
}

int insert_into_hashmap(String& key, int index, hash_node** hash_table)
{
    hash_node* node = new hash_node;
    node->index = index;
    node->key = key;
    int index_in_hashmap;
    for (int i = 0; i < MAX_OFFSET; i++)
    {    
        index_in_hashmap = hash(key, i);
        if (hash_table[index_in_hashmap] == nullptr) {
            hash_table[index_in_hashmap] = node;
            return index_in_hashmap;
        }
    }
    delete node;
    return -1;
}


int index_of_city(String& name, hash_node** hash_table)
{
    int index;
    for (int i = 0; i < MAX_OFFSET; i++)
    {
        index = hash(name, i);
        if (hash_table[index] != nullptr && hash_table[index]->key == name){
            return hash_table[index]->index;
        }
    }
    return -1;
}
hash_node** allocate_hash_table()
{
    hash_node** table = new hash_node*[TABLE_SIZE];
    for (std::size_t i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
    return table;
}

void free_hash_table(hash_node** hash_table)
{
    for (std::size_t i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] != nullptr)
        {
            delete hash_table[i];
        }
    }
    delete[] hash_table;
}