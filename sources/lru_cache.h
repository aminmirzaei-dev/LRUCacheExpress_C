#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <stddef.h>

typedef struct lru_cache lru_cache_t;

lru_cache_t* lru_create(size_t capacity);
int lru_put(lru_cache_t *cache, int key, int value);
int lru_get(lru_cache_t *cache, int key, int *out_value);
void lru_destroy(lru_cache_t *cache);

#endif

