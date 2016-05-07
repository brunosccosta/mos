#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

char* itoa(int value, char* str, uint8_t base)
{
    int idx_str = 0;
    int rem;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (value == 0)
    {
        str[idx_str++] = '0';
        str[idx_str] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (value < 0 && base == 10)
    {
        isNegative = true;
        value = -value;
    }
 
    // Process individual digits
    while (value != 0)
    {
        rem = value % base;
        str[idx_str++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        value = value/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[idx_str++] = '-';
 
    str[idx_str] = '\0'; // Append string terminator
 
    // Reverse the string
    strrev(str);
 
    return str;
}
