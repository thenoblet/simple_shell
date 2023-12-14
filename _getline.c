#include "shell.h"

/**
 * _getline - Custom getline function for reading input from a file descriptor.
 *
 * @lineptr: Pointer to the buffer storing the input line.
 *
 * @n: Pointer to the size of the buffer.
 *
 * @fd: File descriptor to read from.
 *
 * Return: Number of bytes read, or -1 on failure.
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	ssize_t bytes_read = 0;
	size_t position = 0, new_size;
	char str;
	char *buffer;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*lineptr = (char *)malloc(BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUFFER_SIZE;
	}
	while (read(fd, &str, 1) > 0)
	{
		if (position >= *n - 1)
		{
			new_size = *n * 2;
			buffer = (char *)realloc(*lineptr, new_size);
			if (buffer == NULL)
				return (-1);
			*lineptr = buffer;
			*n = new_size;
		}
		(*lineptr)[position++] = str;
		bytes_read++;

		if (str == '\n')
			break;
	}

	if (bytes_read == 0)
		return (-1);

	(*lineptr)[position] = '\0';
	return (bytes_read);
}
