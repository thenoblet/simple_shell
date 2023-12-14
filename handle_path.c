#include "shell.h"

/**
 * execute_with_path - Search for and execute a command using the PATH
 * variable.
 *
 * @lsh: The shell structure containing relevant information.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_with_path(shell_t *lsh)
{
	char path[BUFFER_SIZE];
	path_t *path_list = lsh->path_list;

	/* Iterate through the linked list of directories in the PATH.*/
	while (path_list != NULL)
	{
		/**
		 *  Construct the full path by concatenating the directory, "/",
		 *  and the command.
		 */
		snprintf(path, sizeof(path), "%.*s/%s", (int)(sizeof(path) -
		strlen(lsh->tokenized_commands[0]) - 2), path_list->pathname,
		lsh->tokenized_commands[0]);
		/* printf("Executing: %s\n", path); */


		/* Check if the constructed path is executable. */
		if (access(path, X_OK) == 0)
		{
			/* Execute the command and return the result. */
			return (execute_command(path, lsh));
		}
		/* Check if the command is executable in the current directory.*/
		else if (access(lsh->tokenized_commands[0], X_OK) == 0)
		{
			/* Execute the command and return the result.*/
			return (execute_command(lsh->tokenized_commands[0], lsh));
		}

		/* Move to the next directory in the PATH. */
		path_list = path_list->next;
	}

	return (-1);
}
