#include "htab.h"
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    htab_t *t = htab_init(100);
    printf("size: %d\n", htab_size(t));
    htab_pair_t *pair = htab_lookup_add(t, "hello");
    printf("size: %d\n", htab_size(t));
    bool success = htab_erase(t,"hello");
    printf("size: %d\n", htab_size(t));
    return 0;
}
