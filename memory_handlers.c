#include "shell.h"

/**
 * free_up - Fress memory based on the specified format.
 *
 * @format: A format string indicating the type of date to free.
 *              'u' for user_input (char *).
 *              't' for string array (char *).
 *              'p' for path list (path_t **).
 *
 * @...: Variable arguments based on the format.
 */
void free_up(const char *format, ...)
{
	int i;

	va_list args;
	char *user_input;

	va_start(args, format);

	i = 0;
	while (format[i] != '\0')
	{
		switch (format[i])
		{
		case 'u':
			user_input = va_arg(args, char *);
			safefree(user_input);
			break;
		case 't':
			free_string(va_arg(args, char ***));
			break;
		case 'p':
			free_path_list(va_arg(args, path_t **));
			break;
		default:
			break;
		}
		++i;
	}
	va_end(args);
}
