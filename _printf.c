h#include <stdio.h>
#include <stdarg.h>
/**
 * print_char - Print a single character.
 * @ch: The character to print.
 * @count: Pointer to the count of characters printed.
 */
void print_char(char ch, int *count)
{
	putchar(ch);
	(*count)++;
}
/**
 * print_string - Print a string.
 * @str: The string to print.
 * @count: Pointer to the count of characters printed.
 */
void print_string(const char *str, int *count)
{
	while (*str)
	{
		putchar(*str);
		str++;
		(*count)++;
	}
}
/**
 * _printf - Custom implementation of printf.
 * @format: The format string with zero or more directives.
 *
 * Return: The number of characters printed (excluding the null byte used to end output to strings).
 */
int _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	int count = 0;

	char ch;

	const char *str;

	while (*format)
	{
		if (*format == '%')
		{
			format++; /* Move past the '%' */

			/* Handle the conversion specifiers */
			switch (*format)
			{
				case 'c':
					ch = (char)va_arg(args, int);
					print_char(ch, &count);
					break;
				case 's':
					str = va_arg(args, const char *);
					print_string(str, &count);
					break;
				case '%':
					print_char('%', &count);
					break;
				default:
					print_char('%', &count);
					print_char(*format, &count);
					break;
			}
		}
		else
		{
			print_char(*format, &count);
		}
format++;
}
va_end(args);
return (count);
}
int main(void)
{
	_printf("Hello, %s! This is a test. %c%c\n", "Alice", 'H', 'i');
	return (0);
}
