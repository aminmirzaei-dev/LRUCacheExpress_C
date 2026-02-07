#include "../include/lrucacheexpress.h"
#include <stdio.h>

int main(void)
{
    lru_cache_t *cache = lru_create(2);
    int value;

    lru_put(cache, 1, 10);
    lru_put(cache, 2, 20);

    lru_get(cache, 1, &value);
    printf("%d\n", value);

    lru_put(cache, 3, 30);

    if (lru_get(cache, 2, &value) != 0) {
        printf("Key 2 evicted\n");
    }

    lru_destroy(cache);
    return 0;
}

