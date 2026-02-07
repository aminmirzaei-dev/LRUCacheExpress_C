#include "list.h"
#include <stdlib.h>

int list_init(list_t *list)
{
    if (!list) {
        return -1;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return 0;
}

list_node_t* list_push_front(list_t *list, void *data)
{
    list_node_t *node;

    if (!list) {
        return NULL;
    }

    node = (list_node_t *)malloc(sizeof(list_node_t));
    if (!node) {
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = list->head;

    if (list->head) {
        list->head->prev = node;
    } else {
        /* List was empty */
        list->tail = node;
    }

    list->head = node;
    list->size++;

    return node;
}

void list_remove(list_t *list, list_node_t *node)
{
    if (!list || !node) {
        return;
    }

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        /* Node is head */
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        /* Node is tail */
        list->tail = node->prev;
    }

    free(node);
    list->size--;
}

void list_move_to_front(list_t *list, list_node_t *node)
{
    if (!list || !node || list->head == node) {
        return;
    }

    /* Detach node */
    if (node->prev) {
        node->prev->next = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        /* Node was tail */
        list->tail = node->prev;
    }

    /* Move to front */
    node->prev = NULL;
    node->next = list->head;

    if (list->head) {
        list->head->prev = node;
    }

    list->head = node;

    if (!list->tail) {
        list->tail = node;
    }
}

list_node_t* list_pop_back(list_t *list)
{
    list_node_t *node;

    if (!list || !list->tail) {
        return NULL;
    }

    node = list->tail;

    if (node->prev) {
        node->prev->next = NULL;
        list->tail = node->prev;
    } else {
        /* Only one element */
        list->head = NULL;
        list->tail = NULL;
    }

    node->prev = NULL;
    node->next = NULL;
    list->size--;

    return node;
}

void list_clear(list_t *list)
{
    list_node_t *current;
    list_node_t *next;

    if (!list) {
        return;
    }

    current = list->head;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

