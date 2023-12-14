#include "shell.h"

/**
 * _realloc - reallocate dynamic memory
 *
 * @ptr: pointer to the old memory block
 * @old_size: size of the old memory block
 * @new_size: size of the new memory block
 *
 * Return: a pointer to the newly allocated memory,
 * or NULL if the request failed
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *newMem;
	size_t copySize;

	if (new_size == old_size)
	{
		return (ptr);
	}

	/* handle the free() equivalent call of the _realloc function */
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	newMem = malloc(new_size);
	if (newMem == NULL)
		return (NULL); /* memory allocation failed */

	if (ptr != NULL)
	{
		/* copy size based on minimum of old_size and new_size.*/
		copySize = (old_size < new_size) ? old_size : new_size;

		/* copy content from old memory to new alloc'ed. memory */
		_memcpy(newMem, ptr, copySize);
		free(ptr);
	}
	return (newMem);
}



