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
