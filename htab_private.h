#ifndef __HTAB_PRIVATE__
#define __HTAB_PRIVATE__

#include "htab.h"

struct htab_item
{
    struct htab_pair pair;
    struct htab_item *next;
};

struct htab
{
    size_t size;
    size_t array_size;
    struct htab_item **arr_ptr;
};

typedef struct htab_item htab_item_t;

htab_item_t *htab_find_private(htab_t *t, htab_key_t key, size_t *idx);

#endif