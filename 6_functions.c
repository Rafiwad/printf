#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void print_char(char ch, int *count);
void write_buffer(char *buffer, int size, int *count);
void print_string(const char *str, int *count);
void print_pointer(void *ptr, int *count);
int _printf(const char *format, ...);

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
 * write_buffer - Write the local buffer to stdout.
 * @buffer: The buffer containing the characters to write.
 * @size: The number of characters to write.
 * @count: Pointer to the count of characters printed.
 */
void write_buffer(char *buffer, int size, int *count)
{
	write(1, buffer, size);
	(*count) += size;
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
		print_char(*str, count);
		str++;
	}
}

/**
 * print_pointer - Print a pointer address in hexadecimal.
 * @ptr: The pointer to print.
 * @count: Pointer to the count of characters printed.
 */
void print_pointer(void *ptr, int *count)
{
	unsigned long int address = (unsigned long int)ptr;
	unsigned long int temp = address;
	unsigned long int base = 16;
	char hex[] = "0123456789abcdef";

	print_string("0x", count);

	if (address == 0)
	{
		print_char('0', count);
		return;
	}

	while (temp != 0)
	{
		temp /= base;
		(*count)++;
	}

	while (address != 0)
	{
		unsigned long int digit = address % base;
		print_char(hex[digit], count);
		address /= base;
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
	char buffer[BUFFER_SIZE];
	char *buffer_ptr = buffer;

	while (*format)
	{
		if (*format == '%')
		{
			format++; /* Move past the '%' */

			/* Handle the conversion specifiers */
			switch (*format)
			{
				case 'c':
					*buffer_ptr = (char)va_arg(args, int);
					buffer_ptr++;
					break;
				case 's':
				{
					const char *str = va_arg(args, const char *);
					print_string(str, &count);
					break;
				}
				case 'd':
				case 'i':
				{
					/* Implementation for 'd' and 'i' conversion specifiers */
					/* ... */
					break;
				}
				case 'u':
				{
					/* Implementation for 'u' conversion specifier */
					/* ... */
					break;
				}
				case 'o':
				{
					/* Implementation for 'o' conversion specifier */
					/* ... */
					break;
				}
				case 'x':
				case 'X':
				{
					/* Implementation for 'x' and 'X' conversion specifiers */
					/* ... */
					break;
				}
				case 'p':
				{
					void *ptr = va_arg(args, void *);
					print_pointer(ptr, &count);
					break;
				}
				default:
					*buffer_ptr = '%';
					buffer_ptr++;
					if (*format != '%')
					{
						*buffer_ptr = *format;
						buffer_ptr++;
					}
					break;
			}

			/* If the buffer is full or we have reached the end of the format string */
			if (buffer_ptr - buffer >= BUFFER_SIZE - 1 || *(format + 1) == '\0')
			{
				write_buffer(buffer, buffer_ptr - buffer, &count);
				buffer_ptr = buffer;
			}

			format++;
		}
		else
		{
			*buffer_ptr = *format;
			buffer_ptr++;

			/* If the buffer is full or we have reached the end of the format string */
			if (buffer_ptr - buffer >= BUFFER_SIZE - 1 || *(format + 1) == '\0')
			{
				write_buffer(buffer, buffer_ptr - buffer, &count);
				buffer_ptr = buffer;
			}

			format++;
		}
	}

	va_end(args);
	return (count);
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	int a = 10;
	int *ptr = &a;
	_printf("Value of a: %d\n", a);
	_printf("Address of a: %p\n", ptr);
	return (0);
}
