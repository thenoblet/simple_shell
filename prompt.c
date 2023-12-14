#include "shell.h"

/**
 * prompt - Display the shell prompt
 *
 * Description: This function prints the shell prompt to the standard output,
 * which is typically represented by the "$ " symbol.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("$ ");

	/* Flush the standard output to ensure prompt is displayed */
	fflush(stdout);
}


/**
 * handle_empty_prompt - Handle the case when the user enters an empty prompt
 * @bytes_read: Number of bytes read.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * Description: This function checks if the user entered an empty prompt or
 * CTRL+D was received.
 * If the standard input is a terminal, it prints "exit" to the terminal.
 */
void handle_empty_prompt(ssize_t bytes_read, shell_t *lsh)
{
	/* user entered an empty prompt or CTRL+D was received? */
	if (bytes_read == -1)
	{
		/* Checking if the standard input is a terminal */
		if (isatty(STDIN_FILENO))
		{
			/* Print "exit" to the terminal */
			printf("exit\n");
		}
		exit_shell(lsh, free_up);
	}
}
