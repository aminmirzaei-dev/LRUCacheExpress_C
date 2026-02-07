#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct hash_entry {
    int key;
    void *value;
    struct hash_entry *next;
} hash_entry_t;

typedef struct hash_table {
    hash_entry_t **buckets;
    size_t capacity;
} hash_table_t;

/* Creates a hash table with the given capacity */
hash_table_t* hash_table_create(size_t capacity);

/* Inserts or updates a key-value pair */
int hash_table_put(hash_table_t *table, int key, void *value);

/* Retrieves the value associated with a key, or NULL if not found */
void* hash_table_get(hash_table_t *table, int key);

/* Removes a key from the table */
void hash_table_remove(hash_table_t *table, int key);

/* Frees all resources used by the table */
void hash_table_destroy(hash_table_t *table);

#endif /* HASH_TABLE_H */

