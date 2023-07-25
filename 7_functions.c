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

/* Helper function to print a single character */
void print_char(char ch, int *count)
{
	putchar(ch);
	(*count)++;
}

/* Helper function to write the local buffer to stdout */
void write_buffer(char *buffer, int size, int *count)
{
	write(1, buffer, size);
	(*count) += size;
}

/* Helper function to print a string */
void print_string(const char *str, int *count)
{
	while (*str)
	{
		print_char(*str, count);
		str++;
	}
}

/* Helper function to print a pointer address in hexadecimal */
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

			/* Handle the flag characters */
			int flag_plus = 0;
			int flag_space = 0;
			int flag_hash = 0;
			while (*format == '+' || *format == ' ' || *format == '#')
			{
				if (*format == '+')
					flag_plus = 1;
				else if (*format == ' ')
					flag_space = 1;
				else if (*format == '#')
					flag_hash = 1;
				format++;
			}

			/* Handle the conversion specifiers */
			switch (*format)
			{
				case 'c':
					/* ... */
					break;
				case 's':
					/* ... */
					break;
				case 'd':
				case 'i':
					/* ... */
					break;
				case 'u':
					/* ... */
					break;
				case 'o':
					/* ... */
					break;
				case 'x':
				case 'X':
					/* ... */
					break;
				case 'p':
					/* ... */
					break;
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
