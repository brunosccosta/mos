#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

extern void terminal_putchar(char c);

void printf(const char* data, ...)
{
    const char *p;
    va_list argp;
    int i;
    char *s;
    char fmtbuf[256];

    va_start(argp, data);
    
    for (p = data; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            terminal_putchar(*p);
            continue;
        }
            
        switch(*++p)
		{
		    case 'c':
			    i = va_arg(argp, int);
			    terminal_putchar(i);
			    break;

		    case 'd':
			    i = va_arg(argp, int);
			    s = itoa(i, fmtbuf, 10);
			    printf(s);
			    break;

		    case 's':
			    s = va_arg(argp, char *);
			    printf(s);
			    break;

		    case 'x':
			    i = va_arg(argp, int);
			    s = itoa(i, fmtbuf, 16);
                printf("0x");
			    printf(s);
			    break;

		    case '%':
			    terminal_putchar('%');
			    break;
		}
	}
	va_end(argp);
}
