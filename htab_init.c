#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

htab_t *htab_init(size_t num)
{
    htab_t *t = malloc(sizeof(htab_t));
    if (t == NULL)
    {
        return NULL;
    }

    t->arr_ptr = calloc(num,sizeof(htab_item_t));
    if (t->arr_ptr == NULL)
    {
        return NULL;
    }
    t->array_size = num;
    t->size = 0;

    return t;
}
