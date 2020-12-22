/*
** EPITECH PROJECT, 2020
** name
** File description:
** desc
*/

#include "../include/malloc.h"

static heap_t *split_node(heap_t *node, const size_t size)
{
    heap_t *new_node;

    new_node = node->adress + node->size;
    new_node->adress = node->adress + node->size + sizeof(heap_t);
    new_node->size = size;
    new_node->total_size = node->total_size - node->size - sizeof(heap_t);
    new_node->isFree = false;
    if (node->next)
        node->next->prev = new_node;
    new_node->next = node->next;
    new_node->prev = node;
    node->next = new_node;
    node->total_size = node->size;
    return (new_node);
}

static heap_t *manage_return(heap_t *node, const size_t size,
                                        const bool isSpliting)
{
    if (!node)
        return (NULL);
    if (isSpliting)
        return split_node(node, size);
    node->size = size;
    node->isFree = false;
    return (node);
}

heap_t *best_fit(heap_t *heap, const size_t size)
{
    heap_t *node = NULL;
    size_t min;
    bool isSpliting = false;
    heap_t *tmp = heap;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->isFree && size < tmp->total_size && (!node ||
                                (tmp->total_size - size) < min)) {
            min = tmp->total_size - size;
            node = tmp;
            isSpliting = false;
        } else if (!tmp->isFree && sizeof(heap_t) + size <
                    (tmp->total_size - tmp->size) && (!node ||
                    (tmp->total_size - tmp->size - (sizeof(heap_t) + size))
                    < min)) {
            min = tmp->total_size - tmp->size - (sizeof(heap_t) + size);
            node = tmp;
            isSpliting = true;
        }
    }
    return (manage_return(node, size, isSpliting));
}