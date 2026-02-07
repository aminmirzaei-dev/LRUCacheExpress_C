#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/*
 * Doubly linked list node.
 * The list does not manage the memory of the data pointer.
 */
typedef struct list_node {
    void *data;
    struct list_node *prev;
    struct list_node *next;
} list_node_t;

/*
 * Doubly linked list structure.
 */
typedef struct list {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;

/*
 * Initializes an empty list.
 * Returns 0 on success, non-zero on failure.
 */
int list_init(list_t *list);

/*
 * Inserts a node at the front of the list.
 * Returns the created node or NULL on failure.
 */
list_node_t* list_push_front(list_t *list, void *data);

/*
 * Removes a node from the list.
 * The node itself is freed, but data is not.
 */
void list_remove(list_t *list, list_node_t *node);

/*
 * Moves an existing node to the front of the list.
 */
void list_move_to_front(list_t *list, list_node_t *node);

/*
 * Removes and returns the last node of the list.
 * Returns NULL if the list is empty.
 */
list_node_t* list_pop_back(list_t *list);

/*
 * Clears the list and frees all nodes.
 * Data pointers are not freed.
 */
void list_clear(list_t *list);

#endif /* LIST_H */

