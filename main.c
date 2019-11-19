#include "dragola.h"

/**
 * main - Simple shell
 * @argc: Number of arguments that enter the main.
 * @argv: String of arguments that enter the main.
 * @argenv: Environment Variables.
 *
 * Return: Always successfull (0).
 */
int main(int argc, char *argv[], char *argenv[])
{

	(void) argc;
	(void) argv;

	_simple_shell(argenv);

	return (0);
}
