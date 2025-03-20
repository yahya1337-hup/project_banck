#include <unistd.h>
#include <stdarg.h>

void ft_putstr(char *s)
{
    while (*s)
        write(1, s++, 1);
}

void ft_putnbr(int n)
{
    if (n > 9)
        ft_putnbr(n / 10);

    char c = (n % 10) + '0';
    write(1, &c, 1);
}

int ft_puthex(unsigned int n)
{
    int len = 0;
    char *base = "0123456789abcdef";
    if (n > 15)
        len += ft_puthex(n / 16);
    write(1, &base[n % 16], 1);
    // len += ft_putchar(base[n % 16]);
    return len;
}

int ft_printf(char *format, ...)
{
    va_list ptr;
    int i = 0;

    va_start(ptr, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1] != 0 && format[i + 1] == 's')
            ft_putstr(va_arg(ptr, char *));
        else if (format[i] == '%' && format[i + 1] != 0 && format[i + 1] == 'd')
            ft_putnbr(va_arg(ptr, int));
        else if (format[i] == '%' && format[i + 1] != 0 && format[i + 1] == 'x')
            ft_puthex(va_arg(ptr, int));
        else
            write(1, &format[i], 1);
        i++;
    }
    // va_end ptr;
    return 9;
}

int main()
{
    int i;
    ft_printf("line %s %d %x \n", "yahyaaboumeil", 2006, 255);
}