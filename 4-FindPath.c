#include "dragola.h"

/**
 * create_path - Separates Path in tokens.
 *
 * @P: Pointer to PATH.
 *
 *
 * Return: An array of pointers.
 */

char **create_path(char *P)
{

	int i = 0, colon_counter = 0;
	char *token;
	char **tokenpath;

	while (*(P + i) != '\0')
	{
		if (*(P + i) == ':')
			colon_counter++;
		i++;
	}

	tokenpath = malloc(sizeof(char *) * (colon_counter + 2));/**←REMEMBER!*/
	if (tokenpath == NULL)
		return (NULL);
	i = 0;
	token = strtok(P, "PATH=:");
	while (token != NULL)
	{
		tokenpath[i] = token;
		token = strtok(NULL, ":");
		i++;
	}
	tokenpath[i] = NULL;

	return (tokenpath);
}

/**
 * path_location - Finds the PATH in the set of environment variables.
 *
 * @pat: Array of pointers to the environment variables.
 *
 * Return: → The position in which the PATH is located.
 *         → -1 if it fails to find the PATH.
 *
 */
int path_location(char **pat)
{
	int index = 0, jndex;
	char *_path = "PATH";

	while (pat[index] != NULL)
	{
		jndex = 0;
		while (jndex < 4)
		{
			if (pat[index][jndex] == _path[jndex])
				jndex++;
			else
				break;
		}
		if (jndex == 4)
			break;

		index++;
	}
	if (pat[index] == NULL)
		return (-1);

	return (index);
}

/**
 * find_path - Creates an array of pointers containing the PATH of the system.
 *
 * @argenv: Environment variables of the system.
 *
 * Return: An array of pointers containing the PATH separated in tokens.
 */

char **find_path(char *argenv[])
{
	char **new_path;
	int path_loc;


	path_loc = path_location(argenv);
	if (path_loc == -1)
		return (NULL);

	new_path = create_path(argenv[path_loc]);
	if (new_path == NULL)
		return (NULL);

	return (new_path);

}
