#include "dragola.h"

/**
 * _strlen - Counts the len of a string.
 *
 * @str: string to get the len.
 *
 * Return: Number of characters in the string.
 */
int _strlen(char *str)
{
	int index = 0;

	while (*(str + index) != '\0')
		index++;

	return (index);
}

/**
 * full_path - Combines the input command with the directory in which it is
 *             located.
 *
 * @tokenpath: Environment variables of the system.
 * @command: Inputed command.
 *
 * Return: An array of pointers containing the PATH separated in tokens.
 */

char *full_path(char *tokenpath[], char *command)
{
	int len_com = 0, index_com = 0;
	int len_pat = 0, index_pat = 0, jndex_pat = 0;
	char *com_pat;


	len_com = _strlen(command);

	while (tokenpath[index_pat] != NULL)
	{
		len_pat = _strlen(tokenpath[index_pat]);
		com_pat = malloc(sizeof(char) * (len_com + len_pat + 2));
		if (com_pat == NULL)
			return (NULL);
		jndex_pat = 0;
		while (tokenpath[index_pat][jndex_pat] != '\0')
		{
			com_pat[jndex_pat] = tokenpath[index_pat][jndex_pat];
			jndex_pat++;
		}
		com_pat[jndex_pat] = '/';
		jndex_pat++;
		index_com = 0;

		while (command[index_com] != '\0')
		{
			com_pat[jndex_pat + index_com] = command[index_com];
			index_com++;
		}
		com_pat[jndex_pat + index_com] = '\0';
		index_pat++;

		if (access(com_pat, F_OK) == 0) /** The file exist */
			return (com_pat);
		free(com_pat);
	}
	return (NULL);
}
