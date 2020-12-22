/*
** EPITECH PROJECT, 2020
** name
** File description:
** desc
*/

#include "../include/malloc.h"

static void my_putchar(const char c)
{
    write(1, &c, 1);
}

void my_put_nbr(int nb)
{
    int modulo;

    modulo = 0;
    if (nb <= 9 && nb >= 0)
        my_putchar(nb + '0');
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
        if (nb <= 9 && nb >= 0)
            my_put_nbr(nb);
    }
    if (nb > 9) {
        modulo = nb % 10;
        my_put_nbr(nb / 10);
        my_putchar(modulo + '0');
    }
}

void dump(heap_t *heap)
{
    heap_t *temp = heap;

    for (; temp != NULL; temp = temp->next) {
        write(1, "- ", 2);
        write(1, "isFree: ", 8);
        write(1, (temp->isFree ? "yes " : "no  "), 4);
        write(1, ", total: ", 9);
        my_put_nbr(temp->total_size);
        write(1, ", used: ", 8);
        my_put_nbr(temp->size);
        write(1, "\n", 1);
    }
    write(1, "NULL\n\n", 6);
}