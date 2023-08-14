#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execuut(char *path, char **argv);
int token_split(char *line, char **argv, int *no_token);
/**
 * main - main entrance
 * token_split - token
 * @ac: argument count
 * @argv: arrray of argument pointer
 * Return: always success 0
 */
int main(int ac, char **argv)
{
	char *line;
	char *line_cpy;
	char *token;
	pid_t pid;
	ssize_t j;
	int k;
	const char *delim;
	int w;
	int status;
	int no_token;
	size_t n;
	int linec;
	char *path;

	line = NULL;
	line_cpy = NULL;
	token = NULL;
	path = NULL;
	n = 0;
	linec = 0;
	no_token = 0;
	delim = " \n";
	(void)ac;
	while (1)
	{
		linec++;
		if (isatty(STDIN_FILENO))
		{
			write(1, "($) ", 4);
		}
		j = getline(&line, &n, stdin);
		if (j == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				write(1, "\n", 1);
				return (0);
			}
			return (0);
		}
		if (j == 0)
		{
			write(1, "\n", 1);
			continue;
		}
		if (_strncmp(line, "exit\n", 5) == 0)
		{
			return (0);
		}
		if (_strncmp(line, "env\n", 4) == 0)
		{
			print_env();
			continue;
		}
		line_cpy = malloc(sizeof(char) * (j + 1));
		if (line_cpy == NULL)
		{
			return (-1);
		}
		_strcpy(line_cpy, line);
		token = strtok(line, delim);
		while (token != NULL)
		{
			no_token++;
			token = strtok(NULL, delim);
		}
		no_token++;
		argv = malloc(sizeof(char *) * no_token);
		if (argv == NULL)
		{
			free(line_cpy);
			return (-1);
		}
		token = strtok(line_cpy, delim);
		for (k = 0; token != NULL; k++)
		{
			argv[k] = malloc(sizeof(char) * (_strlen(token) + 1));
			if (argv[k] == NULL)
			{
				free(line_cpy);
				free(argv);
				return (-1);
			}
			_strcpy(argv[k], token);
			token = strtok(NULL, delim);
		}
		argv[k] = NULL;
		if (argv[0] == NULL)
			continue;
		path = get_cmdpath(argv[0]);
		if (!path)
		{
			fprintf(stderr, "./hsh: %d: %s: not found\n", linec, argv[0]);
			continue;
		}
		else
		{
		pid = fork();
		if (pid == -1)
		{
			write(2, "fork failed\n", 13);
			break;
		}
		else if (pid == 0)
		{
			execuut(path, argv);
			continue;
		}
		else
		{
			waitpid(pid, &status, 0);
			perror("waitpid error");
			return (0);
		}
		no_token = 0;
		}
	}
	free(line_cpy);
	for (w = 0; w < no_token - 1; w++)
	{
		free(argv[w]);
	}
	free(argv);
	return (EXIT_SUCCESS);
}
/**
 * execuut - execute command
 * @path: the command path
 * @argv: the command and the argument
 * Return: none
 */
void execuut(char *path, char **argv)
{
	char *mycmd;
	char *myshell;
	int ret;

	myshell = "./hsh";
	mycmd = path;
	ret = execve(mycmd, argv, NULL);
	if (ret == -1)
	{
		perror(myshell);
		exit(1);
	}
}
