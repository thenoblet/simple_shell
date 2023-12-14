#include "shell.h"

/**
 * remove_comments - remove comments from a command before parsing
 * @command: the input command
 *
 * Return: the modified command if # are found
 * or the command itself if no comments are found.
 *
 */
char *remove_comments(char *command)
{
	size_t offset;
	const char *position;
	char *modified_command;

	/* Find the first occurrence of # */
	position = _strchr(command, '#');

	/* If no # is found, return the command */
	if (position == NULL)
		return (command);

	/* Calc. the offset, i.e., the position of the # character in the string */
	offset = position - command;

	/* Check if # is at the start of the string or follows whitespace */
	if (offset == 0 || (offset > 0 && isspace(command[offset - 1])))
	{
		/* Allocate a new string to store the modified command */
		modified_command = malloc(offset + 1);
		if (modified_command == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			safefree(modified_command);
			exit(EXIT_FAILURE);
		}

		/* Copy the relevant portion of the command into the new string */
		_strncpy(modified_command, command, offset);
		modified_command[offset] = '\0';

		return (modified_command);
	}
	else
	{
		/* If # is not at start or following whitespace, return the command */
		return (command);
	}
}
