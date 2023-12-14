#include "shell.h"

/**
 * _memcpy - Copies memory area from source to destination.
 *
 * @dest:  Pointer to the destination memory area.
 * @src: Pointer to the source memory area
 * @n: number of bytes to copy
 *
 * Return: Pointer to the destination memory area (dest)
 */

void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	char *temp_dest = (char *) dest;
	const char *temp_src = (const char *) src;

	for (i = 0; i < n; i++)
	{
		temp_dest[i] = temp_src[i];
	}
	return (dest);
}
