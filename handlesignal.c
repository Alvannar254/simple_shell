#include <unistd.h> /* Standard symbolic constants and types (POSIX) */

/**
 * sigint_handler - Tackles the received terminate signal
 * @s: signal integer, unutilized in the function
 *
 * This function is designed to handle signal interruption (SIGINT).
 * When the user types Ctrl+C, instead of terminating, it prints a new prompt.
 * write() writes data from a buffer into a file descriptor.
 */
void sigint_handler(int __attribute__((unused)) s)
{
	write(1, "\n($) ", 5); /* Writes a new prompt when SIGINT is received */
}

