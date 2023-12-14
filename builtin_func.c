#include "shell.h"

/**
 * _setenv - Set or update an environment variable
 * @name: Name of the environment variable
 * @value: Value to be assigned to the environment variable
 * @overwrite: Flag indicating whether to overwrite an existing value (0 or 1)
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *existing_value, *env_var;

	/* Check if name or value is NULL */
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Error: Name or value cannot be NULL.\n");
		return (-1);
	}

	/* Check if overwrite is a valid value (0 or 1) */
	if (overwrite != 0 && overwrite != 1)
	{
		fprintf(stderr, "Error: Overwrite must be 0 or 1.\n");
		return (-1);
	}

	existing_value = v_getenv(name);
	if (existing_value != NULL)
	{
		if (overwrite != 0)
			_unsetenv(name);
		else
			return (0);
	}

	env_var = malloc(strlen(name) + strlen(value) + 2);
	if (env_var == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return (-1);
	}

	sprintf(env_var, "%s=%s", name, value);
	if (putenv(env_var) != 0)
	{
		fprintf(stderr, "Error: Unable to set environment variable.\n");
		safefree(env_var);
		return (-1);
	}
	return (0);
}

/**
 * _unsetenv - Unset (remove) an environment variable
 * @name: Name of the environment variable to unset
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	size_t name_length;
	char **current, **next, **env;

	if (name == NULL) /* Check if input name is NULL */
	{
		fprintf(stderr, "Error: Input name cannot be NULL.\n");
		return (-1);
	}

	if (v_getenv(name) == NULL) /* Check if the environment variable exists */
	{
		fprintf(stderr, "Error: Environment variable %s does not exist.\n", name);
		return (-1);
	}

	name_length = _strlen(name);
	for (env = environ; *env != NULL; ++env)
	{
		/* Check if the current env. variable matches the specified name */
		if (_strncmp(*env, name, name_length) == 0 && (*env)[name_length] == '=')
		{
			current = env;
			next = env + 1;
			/* Shift the remaining env. variables to remove the unset one */
			while (*current != NULL)
			{
				*current = *next;
				++current;
				++next;
			}
			return (0);
		}
	}
	fprintf(stderr, "Error: Unable to find environment variable %s.\n", name);
	return (-1);
}


/**
 * exit_shell - Handles exiting the shell with a specified exit code.
 * @lsh: Pointer to the shell structure.
 * @func: Function pointer to the free_on_exit function.
 *        This function frees various types of dynamically allocated memory.
 *        Format string specifies the types of arguments to free.
 *        Example: "uptt" means free user_input, path_list, tokens,
 *        tokenized_commands, and command_array.
 * Return: The exit code.
 */
int exit_shell(shell_t *lsh, void (*func)(const char *format, ...))
{
	int exit_code;

	if (lsh->tokenized_commands)
	{
		lsh->exit_status = lsh->tokenized_commands[1];
	}
	else
	{
		lsh->exit_status =  NULL;
	}

	exit_code = lsh->exit_code;

	if (lsh->exit_status == NULL)
	{
		func("upttt", lsh->user_input, &lsh->path_list, &lsh->tokens,
		&lsh->tokenized_commands, &lsh->command_array);
		safefree(lsh);
		exit(exit_code);
	}

	if (_isalpha(*lsh->exit_status) || atoi(lsh->exit_status) < 0
	|| *lsh->exit_status == '-')
	{
		dprintf(STDERR_FILENO, "%s: %lu: exit: Illegal number: %s\n",
		lsh->prog_name, lsh->cmd_count, lsh->exit_status);
		return (2);
	}

	exit_code = atoi(lsh->exit_status);
	func("upttt", lsh->user_input, &lsh->path_list, &lsh->tokens,
	&lsh->tokenized_commands, &lsh->command_array);
	safefree(lsh);
	exit(exit_code);
}

/**
 * _printenv - Print the current environment variables
 *
 * Description:
 *   This function iterates through the environment variables and prints
 *   each one to the standard output. It uses the `environ` external
 *   variable, which is an array of strings representing the
 *   environment variables.
 */
void _printenv(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
