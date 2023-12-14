#include "shell.h"


/**
 * main - Entry point for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: exit code
 */
int main(__attribute__((unused))int argc, char *argv[])
{

	ssize_t bytes_read;
	size_t length = 0;
	shell_t *lsh = NULL;

	lsh = initialise_shell(); /* Initialize the shell structure */
	lsh->prog_name = argv[0]; /* Set the prog. name in the shell struct */

	build_path_list(&lsh->path_list);

	/* Set up the Ctrl+C signal hander */
	setup_signal_handler();

	/* Main shell execution loop */
	while (SHELL_RUNNING)
	{
		prompt(); /* Display the shell prompt to the user */

		/* Read user input from the standard input */
		bytes_read = _getline(&lsh->user_input, &length, STDIN_FILENO);

		++lsh->cmd_count; /* tracks number of shell commands run */

		/* Handle an empty prompt or CTRL+D */
		handle_empty_prompt(bytes_read, lsh);

		lsh->exit_code = parse_input(lsh);

		/* Free the memory allocated for user input */
		safefree(lsh->user_input);
	}

	return (lsh->exit_code); /* return the exit code */
}

