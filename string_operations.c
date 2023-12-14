#include "shell.h"

/**
 * free_string - Frees memory allocated for an array of strings.
 *
 * @string_array: A pointer to an array of strings.
 *
 * Description: This function iterates through the array of strings, frees each
 * string, and then frees the array itself. It also sets the pointer to NULL to
 * prevent dangling references.
 */
void free_string(char ***string_array)
{
	int i = 0;
	char **array;

	if (string_array == NULL || (*string_array) == NULL)
		return;

	array = *string_array;

	for (i = 0; array[i] != NULL; i++)
	{
		safefree(array[i]);
	}

	safefree(array);
	*string_array = NULL;
}

/**
 * _strncpy - Copies up to n characters from the source string to the
 * destination.
 *
 * @dest: The destination string.
 *
 * @src: The source string.
 *
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}


/**
 * _isalpha - checks for alphabetic character.
 *
 * @c: parameter value.
 *
 * Return: Returns 1 if c is a letter, lowercase or uppercase.
 *
 */

int _isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
		return (1);
	}
	else
	{
		return (0);
	}

	return (0);
}

/**
 * _strcmp - compares two strings.
 *
 * @s1:first string.
 * @s2: second string.
 *
 * Return: 0 if @s1 and @s2 are equal, a negative value if @s1 is
 * less than @s2, a positive value if @s1 is greater than @s2.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] -  s2[i]);
		}
		i++;
	}

	return (0);
}
