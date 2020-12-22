/*
** EPITECH PROJECT, 2020
** malloc
** File description:
** malloc header file
*/

#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

typedef struct heap_s
{
    bool isFree;
    size_t size;
    size_t total_size;
    void *adress;
    struct heap_s *next;
    struct heap_s *prev;
} heap_t;

/* malloc */
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

/* best_fit */
heap_t *best_fit(heap_t *heap, const size_t size);

/* node_utils */
heap_t *init_heap(const size_t size);
heap_t *create_node(heap_t *heap, const size_t size);
heap_t *get_node_from_ptr(heap_t *heap, void *ptr);