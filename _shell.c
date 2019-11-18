#include "hshell.h"

/**
 * _simple_shell - Emulates a simple shell.
 *
 *
 * Description - This program emulates a simple shell with its prompt which
 *               waits for the user to input a command.
 *
 *
 *
 * Return: Nothing (Void).
 *
 */

void _simple_shell(char *argenv[])
{
	int writ = 0, rdl, exe, child;
	char *buff;
	char *name[2];
	size_t bytes_read = 1;

	buff = malloc(sizeof(char) * (1));
	if (buff == NULL)
		return;
	while (1)
	{
		writ = write(STDOUT_FILENO, "$ ", 2);
		if (writ == -1)
			write(STDERR_FILENO, "Error\n", 6);
		rdl = getline(&buff, &bytes_read, stdin);
		if (rdl == -1)
		{
			write(STDERR_FILENO, "Error\n", 6);
			exit(98);
		}
		name[0] = buff;
		name[0][7] = '\0';
		name[1] = NULL;
		child = fork();
		if (child == 0)
		{
			exe = execve(buff, name, argenv);
			if (exe == -1)
				write(2, "File or directory not found\n", 28);
		}
		else
		{
			wait(NULL);
		}
	}
}
