#include "shell.h"

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 *
 * return: none
 */

void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n#cisexciting$ ");
	}

