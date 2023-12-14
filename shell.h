#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <signal.h>

/* MACROS */
#define SHELL_RUNNING 1
#define BUFFER_SIZE 1024


/* string manipulation functions */
char **_strtok(const char *str, char *delim);
int countwords(const char *str);
char *copyword(const char *str, int start, int end);
char *_strchr(char *s, char c);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strlen(const char *s);
char *_strdup(char *str);
int _isalpha(int c);
char *_strncpy(char *dest, const char *src, int n);
int _strcmp(char *s1, char *s2);

ssize_t _getline(char **line, size_t *n, int fd);
int resize_buffer(char **lineptr, size_t *buffer_size, size_t total_read);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void *_memcpy(void *dest, const void *src, size_t n);


void prompt(void);

void setup_signal_handler(void);
void signal_handler(int signal_number);


/* environment and PATH handlers */

extern char **environ;

/**
 * struct _path - Represents a node in a linked list for the PATH variable.
 * @pathname: A pointer to a string representing a directory path.
 * @next: A pointer to the next node in the linked list.
 */
typedef struct _path
{
	char *pathname;
	struct _path *next;
} path_t;

path_t *build_path_list(path_t **head);
void print_path_list(path_t *list);
void free_path_list(path_t **list);

char *_getenv(const char *name);
char *v_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void _printenv(void);

/**
 * struct shell - Represents the state of a simple shell.
 * @user_input: The input command string provided by the user.
 * @prog_name: The name of the shell program.
 * @exit_code: The exit code of the last executed command.
 * @command_array: Array of strings representing the parsed commands.
 * @tokenized_commands: an array of tokenized versions of each command
 * @tokens: Array of strings representing individual tokens of a cmd.
 * @token: A single token within the array of tokens.
 * @exit_status: The exit status of the shell.
 * @cmd_count: The count of executed commands.
 * @path_list: Linked list of paths for command execution.
 */
typedef struct shell
{
	char *user_input;
	char *prog_name;
	int exit_code;
	char **command_array;
	char **tokenized_commands;
	char **tokens;
	char *token;
	const char *exit_status;
	size_t cmd_count;
	path_t *path_list;
} shell_t;

shell_t *initialise_shell(void);
void free_up(const char *format, ...);
int exit_shell(shell_t *msh, void (*func)(const char *format, ...));
void handle_empty_prompt(ssize_t bytes_read, shell_t *lsh);
void execute_file_as_input(char *filename, shell_t *msh);

/* command execution and parsing funcs. */
int parse_input(shell_t *lsh);
int execute_command(const char *command, shell_t *lsh);
int execute_tokens(shell_t *lsh, size_t index);
int execute_with_path(shell_t *lsh);
int cmd_not_found(shell_t *lsh);
int parser(shell_t *lsh);
int execute_builtin(shell_t *lsh);
void aux_parser(shell_t *lsh, size_t index);
char *remove_comments(char *command);

/* error handling funcs */
void handle_error(const char *message);

/* custom memory deallocation */
void free_copyword(char *word);
void free_string(char ***string_array);
void _free(void **ptr);

#define safefree(p) _free((void **)&(p))

#endif /* SHELL_H */
