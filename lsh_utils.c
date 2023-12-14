#include "shell.h"

/**
 * initialise_shell - Initialize the shell structure
 *
 * Description: This function allocates memory for a new shell structure,
 * initializes its members to default values, and returns a pointer to the
 * newly created shell.
 *
 * Return: A pointer to the initialized shell structure
 */
shell_t *initialise_shell(void)
{
	/* lets allocate memory for the shell structure */
	shell_t *lsh = malloc(sizeof(shell_t));

	/* memory allocation successful?? */
	if (lsh == NULL)
	{
		/* ah, it wasn't. print error and exit */
		fprintf(stderr, "Failed to start shell...\n");
		exit(-1);
	}

	/* Initialise various members of the shell structure */
	lsh->user_input = NULL;
	lsh->prog_name = NULL;
	lsh->exit_code = 0;
	lsh->command_array = NULL;
	lsh->tokenized_commands = NULL;
	lsh->tokens = NULL;
	lsh->token = NULL;
	lsh->exit_status = NULL;
	lsh->cmd_count = 0;
	lsh->path_list = NULL;

	return (lsh);
}


