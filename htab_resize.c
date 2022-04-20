#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"

void htab_resize(htab_t *t, size_t newn)
{
    htab_t *newT = htab_init(newn);
    for (size_t i = 0; i < t->array_size; i++)
    {
        htab_item_t *tmp = t->arr_ptr[i];
        while (tmp != NULL)
        {
            htab_lookup_add(newT, tmp->pair.key);
            tmp = tmp->next;
        }
    }

    htab_clear(t);
    free(t->arr_ptr);
    t->arr_ptr = calloc(newn,sizeof(htab_item_t));
    for (size_t i = 0; i < newn; i++)
    {
        htab_item_t *tmp = newT->arr_ptr[i];
        while (tmp != NULL)
        {
            htab_lookup_add(t, tmp->pair.key);
            tmp = tmp->next;
        }
    }
    
    
    htab_free(newT);
}