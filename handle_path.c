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

/**
 * execute_file_as_input - Execute commands from a file in a shell
 * @filename: The name of the file containing commands
 * @lsh: Pointer to the shell structure
 *
 * Description:
 *   This function reads commands from a file specified by the
 *   filename parameter, executes each command, and then exits
 *   the shell.
 *   It uses the specified shell structure to store information
 *   about the shell state.
 */
void execute_file_as_input(char *filename, shell_t *lsh)
{
	ssize_t bytes_read;
	int fd;
	size_t length;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_path_list(&lsh->path_list);
		fprintf(stderr, "%s: 0: Can't open %s\n", lsh->prog_name, filename);
		exit(EXIT_FAILURE);
	}

	bytes_read = _getline(&lsh->user_input, &length, fd);

	if (close(fd) == -1)
		fprintf(stderr, "Error: unable to close file descriptor #%d\n", fd);

	if (bytes_read == -1)
	{
		lsh->exit_code = -1;
		exit_shell(lsh, free_up);
	}

	if (bytes_read)
	{
		lsh->prog_name = filename;
		parse_input(lsh);
	}

	exit_shell(lsh, free_up);
}
