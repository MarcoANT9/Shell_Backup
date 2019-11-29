#include "dragola.h"

/**
 * _echo_shell - Emulates a simple shell.
 *
 * @argenv: Environment variables.
 *
 * Description - This program emulates a simple shell with its prompt which
 *               waits for the user to input a command.
 *
 * Return: Nothing (Void).
 *
 */

void _echo_shell(char *argenv[])
{
	int rdl;
	char *buff, **name;
	size_t bytes_read = 512;


	buff = malloc(sizeof(char) * (512)); /** To store input */
	if (buff == NULL)
		return;
	rdl = getline(&buff, &bytes_read, stdin);
	if (rdl == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	name = _interpreter(buff);
	if (name == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(buff);
		return;
	}
	if (access(name[0], F_OK) == -1) /** If the PATH exits or not */
		exe_path(name, 1, argenv);
	else /** Execute if command with PATH is found */
		exe_path(name, 0, argenv);

	free(buff);
	free(name);
}
