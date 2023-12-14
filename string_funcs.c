#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 *
 * @str: string
 *
 * Return: pointer to duplicated string
 */
char *_strdup(char *str)
{
	size_t i, size = 0;
	char *s;
	char *temp;

	/* is the string empty? */
	if (str == NULL)
		return (NULL); /* ah! it is, return NULL */

	/* Create a temporary pointer to keep original string unchanged */
	temp = str;

	while (*temp)
	{
		temp++;
		size++;
	}
	size += 1; /* Add 1 for the null terminator */

	s = (char *)malloc(size * sizeof(char));
	if (s == NULL)
		return (NULL); /* Oops, mem. allocation failed */

	for (i = 0; i < size; ++i)
		s[i] = str[i];

	return (s); /* return pointer to duplicated string */
}


/**
 * _strchr - locates a char in a string
 *
 * @str: string
 * @c: char to be located
 *
 * Return: pointer to @s
 */
char *_strchr(char *str, char c)
{
	/* is the string empty? */
	if (str == NULL)
		return (NULL); /* it is, return NULL */

	while (*str != '\0')
	{
		if (*str == c)
		{
			/* return pointer to matched char */
			return (str);
		}
		str++;
	}

	if (c == '\0')
		return (str);

	return (NULL);
}


/**
 * _strncmp - Compares two strings up to a specified length.
 * @str1: The first string.
 * @str2: The second string.
 * @n: The maximum number of characters to compare.
 *
 * Return: 0 if the strings are equal up to the specified length, otherwise
 * the difference between the first non-matching characters.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i = 0;

	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
		{
			return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
		}
		++i;
	}

	return (0);
}

/**
 * _strlen - returns the length of a string
 *
 * @s: parameter
 *
 * Return: length of a string
 */
int _strlen(const char *s)
{
	int count = 0;

	while (*s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}
