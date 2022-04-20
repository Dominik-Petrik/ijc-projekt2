#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

size_t htab_bucket_count(const htab_t *t)
{
    return t->array_size;
}