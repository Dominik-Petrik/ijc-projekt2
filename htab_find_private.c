#include <stdlib.h>
#include <stdio.h>
#include "htab_private.h"

htab_item_t *htab_find_private(htab_t *t, htab_key_t key, size_t *idx)
{
    size_t result = htab_hash_function(key);
    size_t index = result % t->array_size;
    htab_item_t *tmp = t->arr_ptr[index];
    *idx = index;
    return tmp;
}