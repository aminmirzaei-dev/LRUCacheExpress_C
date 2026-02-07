#include "lru_cache.h"
#include "hash_table.h"
#include "list.h"
#include <stdlib.h>

typedef struct lru_entry {
    int key;
    int value;
    list_node_t *node;
} lru_entry_t;;

struct lru_cache {
    size_t capacity;
    hash_table_t *table;
    list_t list;
};

lru_cache_t* lru_create(size_t capacity)
{
    lru_cache_t *cache;

    if (capacity == 0) {
        return NULL;
    }

    cache = malloc(sizeof(lru_cache_t));
    if (!cache) {
        return NULL;
    }

    cache->table = hash_table_create(capacity * 2);
    if (!cache->table) {
        free(cache);
        return NULL;
    }

    list_init(&cache->list);
    cache->capacity = capacity;

    return cache;
}

int lru_put(lru_cache_t *cache, int key, int value)
{
    lru_entry_t *entry;
    list_node_t *node;

    if (!cache) {
        return -1;
    }

    entry = hash_table_get(cache->table, key);;
    if (entry) {
        entry->value = value;
        list_move_to_front(&cache->list, entry->node);
        return 0;
    }

    if (cache->list.size >= cache->capacity) {
        node = list_pop_back(&cache->list);
        entry = node->data;
        hash_table_remove(cache->table, entry->key);
        free(entry);
        free(node);
    }

    entry = malloc(sizeof(lru_entry_t));
    if (!entry) {
        return -1;
    }

    entry->key = key;
    entry->value = value;
    entry->node = list_push_front(&cache->list, entry);

    return hash_table_put(cache->table, key, entry);
}

int lru_get(lru_cache_t *cache, int key, int *out_value)
{
    lru_entry_t *entry;

    if (!cache || !out_value) {
        return -1;
    }

    entry = hash_table_get(cache->table, key);
    if (!entry) {
        return -1;
    }

    *out_value = entry->value;
    list_move_to_front(&cache->list, entry->node);

    return 0;
}

void lru_destroy(lru_cache_t *cache)
{
    list_node_t *node;
    lru_entry_t *entry;

    if (!cache) {
        return;
    }

    while ((node = list_pop_back(&cache->list)) != NULL) {
        entry = node->data;
        free(entry);
        free(node);
    }

    hash_table_destroy(cache->table);
    free(cache);
}

