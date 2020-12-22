/*
** EPITECH PROJECT, 2020
** name
** File description:
** desc
*/

#include "../include/malloc.h"

static size_t next_page_size(size_t value)
{
    size_t ret = getpagesize();

    while (ret < value) {
        ret *= 2;
    }
    return (ret);
}

heap_t *init_heap(const size_t size)
{
    heap_t *newNode;
    size_t chunk_size = next_page_size(sizeof(heap_t) + size);

    if ((newNode = sbrk(chunk_size)) == (void *)-1)
        return (NULL);
    newNode->isFree = false;
    newNode->size = size;
    newNode->total_size = chunk_size - sizeof(heap_t);
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->adress = (void *)newNode + sizeof(heap_t);
    return (newNode);
}

heap_t *create_node(heap_t *heap, const size_t size)
{
    size_t chunk_size = next_page_size(sizeof(heap_t) + size);
    heap_t *temp = heap;

    for (; temp->next != NULL; temp = temp->next);
    if ((temp->next = sbrk(chunk_size)) == (void *)-1)
        return (NULL);
    temp->next->isFree = false;
    temp->next->size = size;
    temp->next->total_size = chunk_size - sizeof(heap_t);
    temp->next->prev = temp;
    temp->next->next = NULL;
    temp->next->adress = (void *)temp->next + sizeof(heap_t);
    return (temp->next);
}

heap_t *get_node_from_ptr(heap_t *heap, void *ptr)
{
    heap_t *temp = heap;

    for (; temp != NULL; temp = temp->next) {
        if (ptr == temp->adress)
            return (temp);
    }
    return (NULL);
}