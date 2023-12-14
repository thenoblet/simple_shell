#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: the name of the environment variable
 *
 * Return: A pointer to the value in the environment,
 * or NULL if there is no match
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = 0;
	char *temp_name = (char *)name;

	/* Check if the input name or the environment variable is NULL */
	if (name == NULL || environ == NULL)
		return (NULL);

	len = strlen(temp_name); /* let's get the length of the input name.*/

	while (environ != NULL)
	{
		/* Check if the current env. variable matches the input name. */
		if (_strncmp(environ[i], temp_name, len) == 0 && environ[i][len] == '=')
		{
			return (&(environ[i][len + 1]));
		}
		i++;
	}

	return (NULL);
}

/**
 * v_getenv - Get the value of an environment variable
 * @name: Name of the environment variable to retrieve
 *
 * Description:
 *   This function searches for the specified environment variable
 *   by name and returns its value. It iterates through the environment
 *   variables using the external variable `environ`.
 *
 * Return:
 *   If the environment variable is found, the function returns
 *   a pointer to its value.
 *   If the environment variable is not found or if
 *   the input is invalid, it returns NULL.
 */
char *v_getenv(const char *name)
{
	int i;
	char *equals_pos;
	size_t name_length;

	if (name == NULL || *name == '\0')
	{
		/* Invalid input, return NULL */
		return (NULL);
	}

	/* Iterate through the environment variables */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Find the position of the '=' char in the env. variable string */
		equals_pos = _strchr(environ[i], '=');
		if (equals_pos != NULL)
		{
			/* Calculate the length of the name */
			name_length = equals_pos - environ[i];

			/* Check if the current environment variable's name matches the input */
			if (_strncmp(environ[i], name, name_length) == 0 &&
					name_length == strlen(name))
			{
				/* Return the value part of the environment variable */
				return (equals_pos + 1);
			}
		}
	}

	return (NULL);
}

/**
 * build_path_list - builds a linked list from the PATH environment variable
 * @head: a double pointer to the head of the linked list
 *
 * Return: The head of the linked list
 */
path_t *build_path_list(path_t **head)
{
	size_t i = 0;
	char *path_env = NULL, **tokens = NULL;
	path_t *new_node = NULL, *current = NULL;

	path_env = _getenv("PATH");
	if (path_env == NULL || *path_env == '\0')
		return (NULL);

	tokens = _strtok(path_env, ":");
	if (tokens == NULL)
		return (NULL);
	while (tokens[i] != NULL)
	{
		new_node = malloc(sizeof(path_t));
		if (new_node == NULL)
			return (NULL);

		new_node->pathname = strdup(tokens[i]);
		if (new_node->pathname == NULL)
		{
			safefree(new_node);
			return (NULL);
		}
		new_node->next = NULL;

		if (*head == NULL)
			(*head) = new_node;
		else
		{
			current = *head;
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
		}
		safefree(tokens[i]);
		i++;
	}
	free_string(&tokens); /* free tokens */
	return (*head);
}

/**
 * print_path_list - prints the contents of the linked list
 * @list: the head of the linked list
 */
void print_path_list(path_t *list)
{
	/* Check if the linked list is empty. */
	if (list == NULL)
		return;

	/* Iterate through the linked list and print each element. */
	while (list != NULL)
	{
		printf("%s\n", list->pathname);
		list = list->next;
	}
}


/**
 * free_path_list - Frees the memory occupied by the linked list.
 * @list: A double pointer to the head of the linked list.
 */
void free_path_list(path_t **list)
{
	path_t *temp;

	while (*list != NULL)
	{
		temp = (*list);
		(*list) = (*list)->next;
		free(temp->pathname);
		safefree(temp);
	}
}
