#include "io.h"
#include <ctype.h>
#define SPACE 32

int read_word(char *s, int max, FILE *f)
{

    int current;
    int i = 0;
    if ((current = fgetc(f)) == EOF)
    {
        return EOF;
    }
    ungetc(current,f);
    
    while ((current = fgetc(f)) && !isspace(current))
    {
        if (current == EOF)
        {
            ungetc(current, f);
            break;
        }
        if (i < max - 1)
        {
            s[i] = current;
        }
        else
        {
            return -1;
        }
        i++;
    }
    s[i] = '\0';
    return i;
}