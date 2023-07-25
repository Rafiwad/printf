#include <stdio.h>
#include <stdlib.h>

/**
 * print_binary - Print a binary representation of a number.
 * @n: The number to be printed in binary format.
 */
void print_binary(unsigned long int n)
{
	if (n > 1)
		print_binary(n >> 1);

	putchar((n & 1) + '0');
}

/**
 * binary_to_uint - Convert a binary number to an unsigned int.
 * @b: A string containing a binary number.
 *
 * Return: The converted unsigned int number, or 0 if invalid input.
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int result = 0;

	if (b == NULL)
		return (0);

	while (*b)
	{
		if (*b != '0' && *b != '1')
			return (0);

		result = (result << 1) + (*b - '0');
		b++;
	}

	return (result);
}

/**
 * main - Entry point.
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned int n;

	char *binary_string = "101001";

	n = binary_to_uint(binary_string);
	printf("Number: %u\nBinary: ", n);
	print_binary(n);
	putchar('\n');

	return (0);
}
