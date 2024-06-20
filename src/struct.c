#include "headers/struct.h"

void print_list(list_t *list)
{
    list_t *tmp = list;
    while (tmp != NULL)
    {
        printf("(%d, %d)\n", tmp->value.x, tmp->value.y);
        tmp = tmp->next;
    }
}

list_t * free_list(list_t *list)
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