#include "dragola.h"

/**
 * func_put_path - This function will create a PATH for a command.
 *
 * @command: Name of the command.
 * @argenv: Environment variables of the system.
 *
 * Return: → The file with path if it exists in the system.
 *         → NULL if the file does not exist in the system.
 */

char *func_put_path(char *command, char *argenv[])
{

	char **n_path, *_full_path;

	n_path = find_path(argenv); /** 5.FindPath */

	_full_path = full_path(n_path, command); /** 6. AppendPath */

	if (_full_path != NULL)
	{
		free(n_path);
		return (_full_path);
	}

	free(n_path);

	return (NULL);

}
