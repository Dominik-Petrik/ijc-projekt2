#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_private.h"
#define AVG_LEN_MIN 0.5

bool htab_erase(htab_t *t, htab_key_t key)
{
    htab_item_t *item = htab_find_private(t, key, NULL);
    if (item == NULL)
    {
        
        return false;
    }

    htab_item_t *tmp = item;
    htab_item_t *parent = NULL;
    
    do
    {
        if (strcmp(tmp->pair.key,key) == 0)
        {
            if (parent == NULL)
            {
                free((char*)tmp->pair.key);
                free(tmp);
                t->size--;
                float avg = (float)t->size / (float)t->array_size;
                if (avg < AVG_LEN_MIN)
                {
                    htab_resize(t,t->array_size * 2);
                }
                return true;
            }
            else
            {
                parent->next = tmp->next;
                free((char*)tmp->pair.key);
                free(tmp);
                t->size--;
                float avg = (float)t->size / (float)t->array_size;
                if (avg < AVG_LEN_MIN)
                {
                    htab_resize(t,t->array_size * 2);
                }
                return true;
            }
        }
        parent = tmp;
        tmp = tmp->next;
    } while (tmp != NULL);
    return false;
}