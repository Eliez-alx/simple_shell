#include "shell.h"
/**
* print_env - prints the environment string to stdout
*
* Return: 0
*/
int print_env(void)
{
	int i;

	i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, (const void *)environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	exit(EXIT_SUCCESS);
}
