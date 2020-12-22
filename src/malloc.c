/*
** EPITECH PROJECT, 2020
** name
** File description:
** desc
*/

#include "../include/malloc.h"

static heap_t *heap = NULL;

void *malloc(size_t size)
{
    heap_t *node;

    if (size == 0)
        return (NULL);
    if (heap == NULL) {
        if ((heap = init_heap(size)) == NULL)
            return (NULL);
        return (heap->adress);
    } else if ((node = best_fit(heap, size)) != NULL) {
        return (node->adress);
    } else {
        if ((node = create_node(heap, size)) == NULL)
            return (NULL);
        return (node->adress);
    }
    return NULL;
}

void free(void *ptr)
{
    heap_t *temp = heap;

    if (!ptr)
        return;
    temp = ptr - sizeof(heap_t);
    temp->isFree = true;
    if (!temp->prev && !temp->next) {
        heap = NULL;
        sbrk((sizeof(heap_t) + temp->total_size) * -1);
    } else if (temp->prev) {
        temp->prev->total_size += temp->total_size + sizeof(heap_t);
        temp->prev->next = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
    } else if  (temp->next) {
        temp->next->total_size += temp->total_size + sizeof(heap_t);
        temp->next->prev = temp->prev;
        if (temp->prev)
            temp->prev->next = temp->next;
    }
}

void *calloc(size_t nmemb, size_t size)
{
    void *ret = malloc(nmemb * size);

    if (!ret)
        return (NULL);
    ret = memset(ret, 0, nmemb * size);
    return (ret);
}

void *realloc(void *ptr, size_t size)
{
    void *ret;
    heap_t *node_ptr;

    if (!ptr)
        return (malloc(size));
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    node_ptr = ptr - sizeof(heap_t);
    if (node_ptr == NULL || node_ptr->isFree)
        return (NULL);
    ret = malloc(size);
    if (ret)
        ret = memcpy(ret, node_ptr->adress, node_ptr->size);
    free(ptr);
    return (ret);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t check_overflow = nmemb * size;

    if ((nmemb != 0 && check_overflow / nmemb != size) || nmemb == 0 ||
                                                            size == 0) {
        return (NULL);
    }
    return (realloc(ptr, nmemb * size));
}