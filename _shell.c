#include "dragola.h"

/**
 * _interpreter - Simulates the interpreter part of the shell.
 *
 * @buff: Received buffer to write.
 *
 * Description - The shell is composed of three parts, this is the second
 *               part, it takes the input from the prompt and creates the
 *               tokens for execution.
 *
 * Return: An array of char*, NULL if something fails.
 */
char **_interpreter(char *buff)
{
	int index = 0, jndex = 0, kndex = 0, space_counter = 0;
	char **name, *token, *input;

	while (*(buff + index) != '\0') /** This counts spaces */
	{
		if (*(buff + index) == ' ')
			space_counter++;
		index++;
	}
	input = malloc(sizeof(char) * (index + 1));
	if (input == NULL)
		return (NULL);
	name = malloc(sizeof(char *) * (space_counter + 2));
	if (name == NULL)
	{
		free(input);
		return (NULL);
	}
	while (*(buff + jndex) != '\0') /** Copiar buff en input */
	{
		input[jndex] = buff[jndex];
		jndex++;
	}
	input[jndex] = '\0';
	token = strtok(input, " \n");
	while (token != NULL)
	{
		name[kndex] = token;
		token = strtok(NULL, " \n");
		kndex++;
	}
	name[kndex] = NULL;
	return (name);
}

/**
 * _simple_shell - Emulates a simple shell.
 *
 * @argenv: Environment variables.
 *
 * Description - This program emulates a simple shell with its prompt which
 *               waits for the user to input a command.
 *
 * Return: Nothing (Void).
 *
 */

void _simple_shell(char *argenv[])
{
	int writ = 0, exe, child, rdl;
	char *buff;
	char **name;
	size_t bytes_read = 1;

	buff = malloc(sizeof(char) * (1)); /** To store input */
	if (buff == NULL)
		return;
	while (1) /** Perpetual Loop to create shell */
	{
		writ = write(STDOUT_FILENO, "$ ", 2);
		if (writ == -1)
			write(STDERR_FILENO, "Eror\n", 6);
		rdl = getline(&buff, &bytes_read, stdin);
		if (rdl == -1)
			exit(98);
		name = _interpreter(buff);
		if (name == NULL)
		{
			free(buff);
			return;
		}
		child = fork();
		if (child == 0)
		{
			exe = execve(name[0], name, argenv);
			if (exe == -1)
			{
				write(2, "File or directory not found\n", 28);
				free(buff);
				free(name);
			}
		}
		else
		{
			wait(NULL);
		}
	}
}
