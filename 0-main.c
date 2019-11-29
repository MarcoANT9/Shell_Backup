#include "dragola.h"

/**
 * main - Simple shell.
 *
 * @argc: Number of arguments that enter the main.
 * @argv: String of arguments that enter the main.
 * @argenv: Environment Variables.
 *
 * Return: Always successfull (0).
 */
int main(int argc, char *argv[], char *argenv[])
{
	(void) argv;

	if (argc <= 1)
	{
		if (isatty(STDIN_FILENO) != 0)
			_prompt_shell(argenv); /** 2-prompt_shell.c */
		else
			_echo_shell(argenv); /** 1-echo_shell.c */
	}
/**	else */
	/**	_args_shell(argv, argenv); 3-arg_shell.c */

	return (0);
}
