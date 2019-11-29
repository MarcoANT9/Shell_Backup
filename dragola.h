#ifndef DRAGOLA_H
#define DRAGOLA_H

/**========================================================================*/
/**-LIBRARIES--------------------------------------------------------------*/
/**========================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

/**========================================================================*/
/**-STRUCTURES-& DEFINITIONS-----------------------------------------------*/
/**========================================================================*/




/**========================================================================*/
/**-FUNCTIONS--------------------------------------------------------------*/
/**========================================================================*/

/** 1. Simple Shell data from echo */
void _echo_shell(char *argenv[]);

/** 2. Simple Shell with Prompt */
void _prompt_shell(char *argenv[]);
void _prompt(void);
void exe_path(char **name, int mode, char **argenv);
char **copy_env(char **dest, char **argenv);
void free_mem(char *buff, char **name, char **argenv_copy);

/** A. Support */
char **_interpreter(char *buff);
int _exit_(char *buff);

/** 3. Function put the PATH */
char *func_put_path(char *command, char *argenv[]);

/** 4. Create the path */
char **find_path(char *argenv[]);
char **create_path(char *P);
int path_location(char **pat);

/** 5. Combinate command with the folder in which it is located. */
char *full_path(char *tokenpath[], char *command);
int _strlen(char *str);

#endif
