#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"
#define AVG_LEN_MAX 2.0

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    size_t idx = -1;
    htab_item_t *result = htab_find_private(t, key, &idx);
    if (result == NULL)
    {
        result = calloc(1,sizeof(htab_item_t));
        if (result == NULL)
        { 
            return NULL;
        }

        
        result->pair.key = malloc((strlen(key) + 1) * sizeof(char));
        if(result->pair.key == NULL)
        {
            free(result);
            return NULL;
        }
        strcpy((char*)result->pair.key,key);
        result->pair.value = 0;
        t->arr_ptr[idx] = result;
        t->size++;
        float avg = (float)t->size / (float)t->array_size;
        if (avg > AVG_LEN_MAX)
        {
            htab_resize(t,t->array_size * 2);
        }
        return &result->pair;
    }
    else
    {
        htab_item_t *tmp = result;
        do
        {
            if (strcmp(tmp->pair.key,key) == 0)
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
        tmp->pair.key = malloc((strlen(key) + 1) * sizeof(char));
        if(tmp->pair.key == NULL)
        {
            free(tmp);
            return NULL;
        }
        strcpy((char*)tmp->pair.key,key);
        tmp->pair.value = 0;
        t->size++;
        float avg = (float)t->size / (float)t->array_size;
        if (avg > AVG_LEN_MAX)
        {
            htab_resize(t,t->array_size * 2);
        }
        return &tmp->pair;
    }
}