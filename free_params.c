#include "lists.h"
#include "shell.h"
#include <stdlib.h>

/**
 * free_params - Releases memory of param_t structure.
 *
 * @params: Pointer to param_t structure to be released
 *
 * Liberates dynamically assigned memory used by param_t structure,
 * including members: argument array, environment list, input buffer.
 */
void free_params(param_t *params)
{
	unsigned int i;

	/* Check and free memory for buffer */
	if (params->buffer)
		free(params->buffer);
	/* Check and free memory for nextCommand */
	if (params->nextCommand)
		free(params->nextCommand);
	/* Free memory for environment and alias lists */
	free_list(params->env_head);
	free_list(params->alias_head);

	/* Free memory for arguments in a loop */
	for (i = 0; params->args[i]; i++)
		free(params->args[i]);
	free(params->args);

	/* Lastly, free memory for the parameters structure */
	free(params);
}

