#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "io.h"
#define MAX_WORD_LEN 127

void printValues(htab_pair_t *data)
{
    printf("%s\t%d\n", data->key, data->value);
}

int main()
{
    htab_t *t = htab_init(10);
    char word[MAX_WORD_LEN];
    while (read_word(word, MAX_WORD_LEN, stdin) != EOF)
    {
        htab_pair_t *record = htab_lookup_add(t, word);
        record->value++;
    }

    htab_for_each(t, &printValues);

    return 0;
}
