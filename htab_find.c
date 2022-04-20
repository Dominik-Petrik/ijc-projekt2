#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
    htab_item_t *tmp = htab_find_private(t, key,NULL);
    while (tmp != NULL)
    {
        if (strcmp(tmp->pair.key, key) == 0)
        {
            return &tmp->pair;
        }
        tmp = tmp->next;
    }
    return NULL;
}