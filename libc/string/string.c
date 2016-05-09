#include <string.h>

void strswap(char *a, char *b)
{
    char tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;
}

void strrev(char *str)
{
    size_t len = strlen(str);

    int start = 0;
    int end = len - 1;
    while (start < end)
    {
        strswap(str+start, str+end);
        start++;
        end--;
    }
}

size_t strlen(const char *str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    char *c_dest = (char *)dest;
    char *c_src  = (char *)src;

    void *ret = dest;

    while (count--)
    {
        *c_dest++ = *c_src++;
    }

    return ret;
}
