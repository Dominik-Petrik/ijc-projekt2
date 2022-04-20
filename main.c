#include "htab.h"
#include <stdio.h>
#include <stdbool.h>

void printValues(htab_pair_t * data)
{
 printf("KEY: %s - VALUE: %d\n", data->key,data->value);   
}

void addTen(htab_pair_t * data)
{
 data->value += 10;
}


int main(int argc, char const *argv[])
{
    htab_t *t = htab_init(100);
    htab_pair_t *petrik = htab_lookup_add(t,"Petrik");
    htab_pair_t *novak =htab_lookup_add(t,"Novák");
    htab_for_each(t, &printValues);
    htab_for_each(t, &addTen);
    htab_for_each(t, &printValues);
    


    

    return 0;
}
