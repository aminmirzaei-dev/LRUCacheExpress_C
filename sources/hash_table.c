#include "hash_table.h"
#include <stdlib.h>

static size_t hash_int(int key, size_t capacity)
{
    return (size_t)key % capacity;
}

hash_table_t* hash_table_create(size_t capacity)
{
    hash_table_t *table = malloc(sizeof(hash_table_t));
    if (!table) {
        return NULL;
    }

    table->buckets = calloc(capacity, sizeof(hash_entry_t *));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    table->capacity = capacity;
    return table;
}

int hash_table_put(hash_table_t *table, int key, void *value)
{
    hash_entry_t *entry;
    size_t index;

    if (!table) {
        return -1;
    }

    index = hash_int(key, table->capacity);
    entry = table->buckets[index];

    while (entry) {
        if (entry->key == key) {
            entry->value = value;
            return 0;
        }
        entry = entry->next;
    }

    entry = malloc(sizeof(hash_entry_t));
    if (!entry) {
        return -1;
    }

    entry->key = key;
    entry->value = value;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;

    return 0;
}

void* hash_table_get(hash_table_t *table, int key)
{
    hash_entry_t *entry;
    size_t index;

    if (!table) {
        return NULL;
    }

    index = hash_int(key, table->capacity);
    entry = table->buckets[index];

    while (entry) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

void hash_table_remove(hash_table_t *table, int key)
{
    hash_entry_t *entry;
    hash_entry_t *prev = NULL;
    size_t index;

    if (!table) {
        return;
    }

    index = hash_int(key, table->capacity);
    entry = table->buckets[index];

    while (entry) {
        if (entry->key == key) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table->buckets[index] = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void hash_table_destroy(hash_table_t *table)
{
    size_t i;
    hash_entry_t *entry;
    hash_entry_t *next;

    if (!table) {
        return;
    }

    for (i = 0; i < table->capacity; i++) {
        entry = table->buckets[i];
        while (entry) {
            next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(table->buckets);
    free(table);
}

