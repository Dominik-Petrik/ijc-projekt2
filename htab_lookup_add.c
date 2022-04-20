#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    size_t idx = -1;
    htab_item_t *result = htab_find_private(t, key, &idx);
    if (result == NULL)
    {
        printf("notgood");
        result = malloc(sizeof(htab_item_t));
        if (result == NULL)
        { 
            return NULL;
        }
        
        result->pair.key = key;
        result->pair.value = 0;
        t->arr_ptr[idx] = result;
        t->size++;
        return &result->pair;
    }
    else
    {
        htab_item_t *tmp = result;
        do
        {
            if (strcmp(tmp->pair.key, key) == 0)
            {
                return &tmp->pair;
            }
            tmp = tmp->next;
        } while (tmp != NULL);

        tmp = malloc(sizeof(htab_item_t));
        if (tmp == NULL)
        {
            return NULL;
        }
        tmp->pair.key = key;
        tmp->pair.value = 0;
        t->size++;
        return &tmp->pair;
    }
}