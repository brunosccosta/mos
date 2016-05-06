#include <stdarg.h>

#include <kernel/tty.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_default_color, terminal_current_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_default_color = terminal_current_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_default_color);
        }
    }
}
 
void terminal_setcolor(uint8_t color)
{
    terminal_current_color = color;
}

void terminal_set_default_color()
{
    terminal_setcolor(terminal_default_color);
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
	switch (c)
	{
		case '\n':
			terminal_newline();
			break;
		default:
			terminal_regularchar(c);
			break;
	}
}

void terminal_newline()
{
	terminal_column = 0;
	terminal_row++;
}

void terminal_regularchar(char c)
{
	terminal_putentryat(c, terminal_current_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }
}
 
void terminal_writestring(const char* data, ...)
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
			    terminal_putchar(s);
			    break;

		    case 's':
			    s = va_arg(argp, char *);
			    terminal_putchar(s);
			    break;

		    case 'x':
			    i = va_arg(argp, int);
			    s = itoa(i, fmtbuf, 16);
			    terminal_putchar(s);
			    break;

		    case '%':
			    terminal_putchar('%');
			    break;
		}
	}
	va_end(argp);
}









