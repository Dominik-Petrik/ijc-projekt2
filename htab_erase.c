#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

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
        if (tmp->pair.key == key)
        {
            if (parent == NULL)
            {
                free(tmp);
                t->size--;
                return true;
            }
            else
            {
                parent->next = tmp->next;
                free(tmp);
                t->size--;
                return true;
            }
        }
        parent = tmp;
        tmp = tmp->next;
    } while (tmp != NULL);
    return false;
}