#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t *t)
{
    for (size_t i = 0; i < t->array_size; i++)
    {
        htab_item_t *tmp = t->arr_ptr[i];
        htab_item_t *current = NULL;
        while (tmp != NULL)
        {
            current = tmp;
            tmp = current->next;
            free((char*)current->pair.key);
            free(current);
            t->size--;
        }
        free(tmp);
    }
}