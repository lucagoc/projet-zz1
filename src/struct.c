#include "headers/struct.h"

/**
 * @file struct.c
 * @brief Définition des structures
 * @version 1.0
 */

/**
 * @brief Affiche une liste de cases
 *
 * @param list Liste de cases
 */
void print_list(list_t *list)
{
    list_t *tmp = list;
    while (tmp != NULL)
    {
        printf("(%d, %d)\n", tmp->value.x, tmp->value.y);
        tmp = tmp->next;
    }
}

/**
 * @brief Libère la mémoire d'une liste de cases
 *
 * @param list Liste de cases
 * @return list_t* Liste de cases
 */
list_t *free_list(list_t *list)
{
    list_t *tmp = list;
    while (tmp != NULL)
    {
        list_t *next = tmp->next;
        free(tmp);
        tmp = next;
    }

    return NULL;
}