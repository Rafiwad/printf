#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

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
	char buffer[1024];
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
					while (*str)
					{
						*buffer_ptr = *str;
						buffer_ptr++;
						str++;
					}
					break;
				}
				case 'd':
				case 'i':
				{
					int num = va_arg(args, int);
					int temp = num;

					if (num < 0)
					{
						*buffer_ptr = '-';
						buffer_ptr++;
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
						*buffer_ptr = digit + '0';
						buffer_ptr++;
						num %= divisor;
						divisor /= 10;
					} while (divisor != 0);
					break;
				}
				case 'u':
				{
					unsigned int unum = va_arg(args, unsigned int);
					unsigned int temp = unum;
					unsigned int divisor = 1;

					if (unum == 0)
					{
						*buffer_ptr = '0';
						buffer_ptr++;
						break;
					}

					while (temp / 10 != 0)
					{
						divisor *= 10;
						temp /= 10;
					}

					do
					{
						unsigned int digit = unum / divisor;
						*buffer_ptr = digit + '0';
						buffer_ptr++;
						unum %= divisor;
						divisor /= 10;
					} while (divisor != 0);
					break;
				}
				case 'o':
				{
					unsigned int unum = va_arg(args, unsigned int);

					if (unum == 0)
					{
						*buffer_ptr = '0';
						buffer_ptr++;
						break;
					}

					int octalNum[100];
					int i = 0;

					while (unum != 0)
					{
						octalNum[i] = unum % 8;
						unum /= 8;
						i++;
					}

					for (int j = i - 1; j >= 0; j--)
					{
						*buffer_ptr = octalNum[j] + '0';
						buffer_ptr++;
					}
					break;
				}
				case 'x':
				{
					unsigned int unum = va_arg(args, unsigned int);

					if (unum == 0)
					{
						*buffer_ptr = '0';
						buffer_ptr++;
						break;
					}

					int rem;
					char hex[100];
					int i = 0;

					while (unum != 0)
					{
						rem = unum % 16;

						if (rem < 10)
							hex[i] = rem + '0';
						else
							hex[i] = rem - 10 + 'a';

						unum /= 16;
						i++;
					}

					for (int j = i - 1; j >= 0; j--)
					{
						*buffer_ptr = hex[j];
						buffer_ptr++;
					}
					break;
				}
				case 'X':
				{
					unsigned int unum = va_arg(args, unsigned int);

					if (unum == 0)
					{
						*buffer_ptr = '0';
						buffer_ptr++;
						break;
					}

					int rem;
					char hex[100];
					int i = 0;

					while (unum != 0)
					{
						rem = unum % 16;

						if (rem < 10)
							hex[i] = rem + '0';
						else
							hex[i] = rem - 10 + 'A';

						unum /= 16;
						i++;
					}

					for (int j = i - 1; j >= 0; j--)
					{
						*buffer_ptr = hex[j];
						buffer_ptr++;
					}
					break;
				}
				case '%':
					*buffer_ptr = '%';
					buffer_ptr++;
					break;
				default:
					*buffer_ptr = '%';
					buffer_ptr++;
					*buffer_ptr = *format;
					buffer_ptr++;
					break;
			}
		}
		else
		{
			*buffer_ptr = *format;
			buffer_ptr++;
		}

		/* Write the buffer if it's full or we have reached the end of the format string */
		if (buffer_ptr - buffer >= sizeof(buffer) - 1 || *(format + 1) == '\0')
		{
			write_buffer(buffer, buffer_ptr - buffer, &count);
			buffer_ptr = buffer;
		}

		format++;
	}

	va_end(args);
	return (count);
}

int main(void)
{
	_printf("%d, %i, %u, %o, %x, %X\n", 123, -456, 789, 123, 123, 123);
	return (0);
}
