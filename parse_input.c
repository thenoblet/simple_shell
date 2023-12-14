#include "shell.h"

/**
 * parse_input - Parse user input and execute commands.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * Return: Exit code of the last executed command or -1 on failure.
 */
int parse_input(shell_t *lsh)
{
	size_t i;

	if (*lsh->user_input == '\n' || *lsh->user_input == '#')
		return (0);

	/* remove comments if any */
	lsh->user_input = remove_comments(lsh->user_input);

	lsh->command_array = _strtok(lsh->user_input, "\n");
	if (lsh->command_array == NULL)
	{
		return (-1);
	}

	for (i = 0; lsh->command_array[i] != NULL; i++)
	{
		lsh->token = lsh->command_array[i];

		lsh->tokens = _strtok(lsh->token, ";\n");
		if (lsh->tokens == NULL)
		{
			fprintf(stderr, "Couldn't allocate memory\n");
			safefree(lsh->command_array);
			return (-1);
		}

		lsh->exit_code = parser(lsh);
		free_string(&lsh->tokens);
	}

	free_string(&lsh->command_array);
	return (lsh->exit_code);
}

/**
 * parser - Parse and executes tokens.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * Return: Exit code of the last executed command or -1 on failure.
 */
int parser(shell_t *lsh)
{
	size_t i;

	for (i = 0; lsh->tokens[i] != NULL; i++)
	{
		lsh->exit_code = execute_tokens(lsh, i);
		safefree(lsh->tokens[i]);
	}
	free_string(&lsh->tokens);

	return (lsh->exit_code);
}

/**
 * execute_tokens - Executes individual tokens.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * @index: Index of the token in the token array.
 *
 * Return: Exit code of the executed command or -1 on failure.
 */
int execute_tokens(shell_t *lsh, size_t index)
{
		lsh->tokenized_commands = _strtok(lsh->tokens[index], NULL);
		if (lsh->tokenized_commands == NULL)
		{
			return (0);
		}
		if (lsh->tokenized_commands[0] != NULL && lsh->tokenized_commands != NULL)
		{
			aux_parser(lsh, index);
		}
		else
		{
			free_string(&lsh->tokenized_commands);
		}

		if (lsh->tokenized_commands != NULL)
		{
			safefree(lsh->tokenized_commands);
		}


		safefree(lsh->tokens[index]);
		return (lsh->exit_code);
}

/**
 * cmd_not_found - Handle command not found error.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * Return: Exit code for command not found (127).
 */
int cmd_not_found(shell_t *lsh)
{
	dprintf(STDERR_FILENO, "%s: %lu: %s: not found\n", lsh->prog_name,
			lsh->cmd_count, lsh->tokenized_commands[0]);

	return (127); /* command not found */
}

/**
 * aux_parser - Auxiliary function to parse and execute commands.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * @index: Index of the tokenized command to be processed.
 */
void aux_parser(shell_t *lsh, size_t index __attribute__((unused)))
{
			lsh->exit_code = execute_builtin(lsh);
			if (lsh->exit_code != 18)
			{
				free_string(&lsh->tokenized_commands);
				return;
			}

			if (lsh->path_list != NULL && !_strchr(lsh->tokenized_commands[0], '/'))
			{
				lsh->exit_code = execute_with_path(lsh);
				if (lsh->exit_code == -1)
				{
					lsh->exit_code = cmd_not_found(lsh);
				}
			}
			else
			{
				if (access(lsh->tokenized_commands[0], X_OK) == 0 &&
				_strchr(lsh->tokenized_commands[0], '/'))
				{
					lsh->exit_code = execute_command(lsh->tokenized_commands[0], lsh);
				}
				else
				{
					lsh->exit_code = cmd_not_found(lsh);
				}
			}

			free_string(&lsh->tokenized_commands);
}
