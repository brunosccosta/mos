#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

void strswap(char *a, char *b);
void strrev(char *str);
size_t strlen(const char *str);

void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *ptr, unsigned char value, size_t count);

#endif
