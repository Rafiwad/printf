#include <stdio.h>
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
 * print_integer - Print a signed integer.
 * @num: The integer to print.
 * @count: Pointer to the count of characters printed.
 */
void print_integer(int num, int *count)
{
	int temp = num;

	if (num < 0)
	{
		print_char('-', count);
		num = -num;
	}

	int divisor = 1;
	while (temp / 10 != 0)
	{
		divisor *= 10;
		temp /= 10;
	}

	do
	{
		int digit = num / divisor;
		print_char(digit + '0', count);
		num %= divisor;
		divisor /= 10;
	} while (divisor != 0);
}

/**
 * print_unsigned - Print an unsigned integer.
 * @num: The unsigned integer to print.
 * @count: Pointer to the count of characters printed.
 */
void print_unsigned(unsigned int num, int *count)
{
	if (num == 0)
	{
		print_char('0', count);
		return;
	}

	unsigned int temp = num;
	unsigned int divisor = 1;

	while (temp / 10 != 0)
	{
		divisor *= 10;
		temp /= 10;
	}

	do
	{
		unsigned int digit = num / divisor;
		print_char(digit + '0', count);
		num %= divisor;
		divisor /= 10;
	} while (divisor != 0);
}

/**
 * print_octal - Print an unsigned integer in octal format.
 * @num: The unsigned integer to print.
 * @count: Pointer to the count of characters printed.
 */
void print_octal(unsigned int num, int *count)
{
	if (num == 0)
	{
		print_char('0', count);
		return;
	}

	int octalNum[100];
	int i = 0;

	while (num != 0)
	{
		octalNum[i] = num % 8;
		num /= 8;
		i++;
	}

	for (int j = i - 1; j >= 0; j--)
	{
		print_char(octalNum[j] + '0', count);
	}
}

/**
 * print_hex - Print an unsigned integer in lowercase hexadecimal format.
 * @num: The unsigned integer to print.
 * @count: Pointer to the count of characters printed.
 */
void print_hex(unsigned int num, int *count)
{
	if (num == 0)
	{
		print_char('0', count);
		return;
	}

	int rem;
	char hex[100];
	int i = 0;

	while (num != 0)
	{
		rem = num % 16;

		if (rem < 10)
			hex[i] = rem + '0';
		else
			hex[i] = rem - 10 + 'a';

		num /= 16;
		i++;
	}

	for (int j = i - 1; j >= 0; j--)
	{
		print_char(hex[j], count);
	}
}

/**
 * print_hex_upper - Print an unsigned integer in uppercase hexadecimal format.
 * @num: The unsigned integer to print.
 * @count: Pointer to the count of characters printed.
 */
void print_hex_upper(unsigned int num, int *count)
{
	if (num == 0)
	{
		print_char('0', count);
		return;
	}

	int rem;
	char hex[100];
	int i = 0;

	while (num != 0)
	{
		rem = num % 16;

		if (rem < 10)
			hex[i] = rem + '0';
		else
			hex[i] = rem - 10 + 'A';

		num /= 16;
		i++;
	}

	for (int j = i - 1; j >= 0; j--)
	{
		print_char(hex[j], count);
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
	int num;
	unsigned int unum;

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
				case 'd':
				case 'i':
					num = va_arg(args, int);
					print_integer(num, &count);
					break;
				case 'u':
					unum = va_arg(args, unsigned int);
					print_unsigned(unum, &count);
					break;
				case 'o':
					unum = va_arg(args, unsigned int);
					print_octal(unum, &count);
					break;
				case 'x':
					unum = va_arg(args, unsigned int);
					print_hex(unum, &count);
					break;
				case 'X':
					unum = va_arg(args, unsigned int);
					print_hex_upper(unum, &count);
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
