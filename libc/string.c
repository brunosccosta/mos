#include "string.h"

#include <stdint.h>

void int_to_ascii(int n, char str[]) {
    int idx = 0;
    int sgn = n;

    if (n < 0) n = -n;

    do
    {
        int unidade = n % 10;
        char c_unidade = (char) (unidade + '0');
        str[idx++] = c_unidade;

        n = n / 10;
    } while (n > 0);
    
    if (sgn < 0) str[idx++] = '-';
    str[idx++] = '\0';

    reverse(str);
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}

int strlen(char s[]) {
    int i=0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void backspace(char s[]) {
    int i=strlen(s)-1;
    if (i>0) s[i] = '\0';
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}