#include <stdio.h>
#include <stdlib.h>

static int xctod(int c)
{
    if (isdigit(c))
        return c - '0';
    else if (isupper(c))
        return c - 'A' + 10;
    else if (islower(c))
        return c - 'a' + 10;
    else
        return 0;
}

char *unescstring(char *src, int srclen, char *dest, int destsize)
{
    char *endp = src + srclen;
    char *srcp;
    char *destp = dest;
    int nwrote = 0;

    for (srcp = src; srcp < endp; srcp++)
    {
        if (nwrote > destsize)
            return NULL;
        if(*srcp == '+')
            *destp++ = ' ';
        else
            if(*srcp == '%')
            {
                *destp++ = (xctod(*(srcp+1)) << 4) + xctod(*(srcp+2));
                srcp += 2;
            }
            else
                *destp++ = *srcp;
        nwrote++;
    }

    *destp = '\0';

    return dest;
}
