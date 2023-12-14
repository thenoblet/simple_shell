#include "shell.h"

/**
 * _free - Frees/deallocates a pointer/dynamically allocated memory
 * and sets it to NULL.
 *
 * @ptr: A pointer to the pointer to be freed.
 *
 * Description: This function takes a pointer to a pointer and
 * frees the memory it points to, then sets the original pointer to
 * NULL to avoid dangling pointers.
 *
 * Note: explicitly cast the pointer type to void when you call `_free`.
 */

void _free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
