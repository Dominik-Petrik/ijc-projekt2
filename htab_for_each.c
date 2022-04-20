#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{
    for (size_t i = 0; i < t->array_size; i++)
    {

        htab_item_t *tmp = t->arr_ptr[i];
        htab_key_t savedKey;
        while (tmp != NULL)
        {
            savedKey = tmp->pair.key;
            f(&tmp->pair);
            if (strcmp(tmp->pair.key, savedKey) != 0)
            {
                strcpy((char*)tmp->pair.key, savedKey);
            }
            tmp = tmp->next;
        }
    }
}