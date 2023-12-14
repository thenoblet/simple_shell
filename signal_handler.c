#include "shell.h"

static sig_atomic_t interrupted;
/**
 * initialize_interrupted - Function to initialize the 'interrupted' variable.
 */
void initialize_interrupted(void)
{
	interrupted = 0;
}


/**
 * signal_handler - Signal handler function for SIGINT (Ctrl+C).
 * @signal_number: The signal number (SIGINT in this case).
 *
 * Description: Handles the SIGINT signal, which is generated when the user
 * presses Ctrl+C. Sets the 'interrupted' flag to 1 to indicate a Ctrl+C
 * interruption. Prints a new prompt after Ctrl+C.
 */
void signal_handler(int signal_number __attribute__((unused)))
{
	interrupted = 1;
	write(STDOUT_FILENO, "\n$ ", 3);  /* Print a new prompt after Ctrl+C */
}

/**
 * setup_signal_handler - Sets up the Ctrl+C signal handler using the signal
 * function.
 *
 * Description: Configures the signal handling behavior for Ctrl+C (SIGINT)
 * using the signal function. Associates the sigint_handler function as the
 * handler for SIGINT. Uses the signal function to register the handler and
 * returns the previous handler. Note: The signal function has limitations, and
 * the use of sigaction is recommended for more advanced signal handling.
 */
void setup_signal_handler(void)
{
	signal(SIGINT, signal_handler);
}
