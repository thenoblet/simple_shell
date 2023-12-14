#include "shell.h"

/**
 * execute_command - Executes a shell command using fork and execve.
 *
 * @command: The command to execute.
 *
 * @lsh: Pointer to the shell structure containing relevant information.
 *
 * Return: Exit status of the executed command or -1 on failure.
 */
int execute_command(const char *command, shell_t *lsh)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
		handle_error("fork failed");

	if (pid == 0)
	{
		if (execve(command, lsh->tokenized_commands, environ) == -1)
		{
			if (errno == EACCES)
			{
				fprintf(stderr, "%s: %lu: %s\n", lsh->prog_name, lsh->cmd_count,
				strerror(errno));
				return (127);
			}

			perror("execve");
			return (-1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("wait");
			return (-1);
		}
		if (WIFEXITED(status))
		{
			/* normal termination */
			return (WEXITSTATUS(status));
		}
	}

	return (0);
}
