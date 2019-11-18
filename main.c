#include "hshell.h"

/**
 * main - Simple shell
 *
 *
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
