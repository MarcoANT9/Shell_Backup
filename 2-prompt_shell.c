#include "dragola.h"

/**
 * _prompt- Prints a prompt
 *
 * Return: Nothing (void)
 */
void _prompt(void)
{
	int writ;

	writ = write(STDOUT_FILENO, "$ ", 2);
	if (writ == -1)
	{
		write(STDIN_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * exe_path - Executes a function.
 *
 * @name: Array of char *.
 * @mode: Mode of operation: → 1 for when the path is not present or wrong.
 *                           → 0 for when the path is right.
 * @argenv: Environment variables.
 *
 * Return - Nothing (void).
 */
void exe_path(char **name, int mode, char **argenv)
{
	int exe, index = 0;
	int str_len = _strlen(name[0]);
	char *command;

	command = malloc(sizeof(char) * (str_len + 1));

	while (name[0][index] != '\0')
	{
		command[index] = name[0][index];
		index++;
	}

	if (mode == 1)
	{
		name[0] = func_put_path(name[0], argenv);
		exe = execve(name[0], name, argenv);
		if (exe == -1)
		{
			write(2, command, str_len);
			write(2, ": command not found\n", 20);
		}
		free(name[0]);
	}
	else
	{
		exe = execve(name[0], name, argenv);
		if (exe == -1)
		{
			write(2, command, str_len);
			write(2, ": command not found\n", 20);
		}
	}
	free(command);
}

/**
 * copy_env - Copies the environment.
 *
 * @dest: Array of pointers to copy the envars.
 * @argenv: List of envars.
 *
 * Return: An array of pointers containing a copy of the envars.
 */
char **copy_env(char **dest, char **argenv)
{
	int index_envi = 0, jndex_envi;

	while (argenv[index_envi] != NULL)
		index_envi++;
	dest = malloc(sizeof(char *) * (index_envi + 1));
	if (dest == NULL)
		return (NULL);
	index_envi = 0;
	while (argenv[index_envi] != NULL)
	{
		jndex_envi = 0;
		while (argenv[index_envi][jndex_envi] != '\0')
			jndex_envi++;
		dest[index_envi] = malloc(sizeof(char) * (jndex_envi + 1));
		if (dest[index_envi] == NULL)
		{
			index_envi--;
			while (index_envi != 0)
			{
				free(dest[index_envi]);
				index_envi--;
			}
			free(dest);
			return (NULL);
		}
		jndex_envi = 0;
		while (argenv[index_envi][jndex_envi] != '\0')
		{
			dest[index_envi][jndex_envi] =
				argenv[index_envi][jndex_envi];
			jndex_envi++;
		}
		argenv[index_envi][jndex_envi] = '\0';
		index_envi++;
	}
	dest[index_envi] = NULL;
	return (dest);
}

/**
 * free_mem - Free memory.
 *
 * @buff: Input reading buffer.
 * @name: Array of pointers containing command and args.
 * @argenv_copy: Envar copy.
 *
 * Return: Nothing (void).
 */

void free_mem(char *buff, char **name, char **argenv_copy)
{
	int index_env = 0;

	free(buff);
	free(name);
	while (argenv_copy[index_env] != NULL)
	{
		free(argenv_copy[index_env]);
		index_env++;
	}
	free(argenv_copy[index_env]);
	free(argenv_copy);
}

/**
 * _prompt_shell - Emulates a simple shell.
 *
 * @argenv: Environment variables.
 *
 * Description - This program emulates a simple shell with its prompt which
 *               waits for the user to input a command.
 *
 * Return: Nothing (Void).
 *
 */

void _prompt_shell(char *argenv[])
{
	int rdl, mode = 0, status; /** Execute and read line */
	char *buff, **name, **argenv_copy;
	pid_t child;
	size_t bytes_read = 20;

	do {
		_prompt();
		buff = malloc(sizeof(char) * 20);
		if (buff == NULL)
			return;
		rdl = getline(&buff, &bytes_read, stdin);
		if (rdl == -1 || _exit_(buff) == 1)
		{
			if (_exit_(buff) == 0)
				write(STDOUT_FILENO, "\n", 1);
			free(buff);
			exit(0);
		}
		argenv_copy = copy_env(argenv_copy, argenv);
		name = _interpreter(buff);
		if (name == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			free_mem(buff, name, argenv_copy);
			exit(0);
		}
		child = fork();
		if (child == 0)
		{
			if (access(name[0], F_OK) == -1) /**Command has path?*/
				exe_path(name, 1, argenv_copy);
			else /** Execute if command with PATH is found */
				exe_path(name, 0, argenv_copy);
			free_mem(buff, name, argenv_copy);
			exit(0);
		}
		else
		{
			wait(&status);
		}
	} while (mode == 0);
}
