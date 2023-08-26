#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main((int argc, char *argv[]) __attribute__(unused), char **env);
int _execute(char *arguments, struct stat *statbuf, char **envp);
bool check_file_status(char *pathname, struct stat *statbuf);
void handle_error(pid_t pid);
char **split_string(const char *str, const char *delimiter, int *count);
void free_substrings(char **substrings, int count);

/**
 * main - Shell program to run commands
 * @argc: Argument count
 * @argv: Argument vector
 * @env: Parameter
 * Return: 0 on success
*/

int main((int argc, char *argv[]) __attribute__(unused), char **env)
{
	char *buff = NULL, *prompt = "$";
	size_t buff_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus;
	bool from_pipe = false;
	struct stat statbuf;

	while (1 && !from_pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			from_pipe = true;
		write(STDOUT_FILENO, prompt, 1);
		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			perror("Error (getline)");
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';
		wpid = fork();
		if (wpid == -1)
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		if (wpid == 0)
			_execute(buff, &statbuf, env);
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("ERROR (wait)");
			exit(EXIT_FAILURE);
		}
	}
	free(buff);
	return (0);
}

/**
 * _execute - Execute
 * @envp: Environment variable
 * @arguments: Command arguments
 * @statbuf: Buffer for file status
 * Return: on success
*/
int _execute(char *arguments, struct stat *statbuf, char **envp)
{
	int argc;
	char **argv;

	char *exe__attribute__(unused);
	argv = split_string(arguments, " ", &argc);
	if (!check_file_status(argv[0], statbuf))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	execve(argv[0], argv, envp);
	perror("Error (execute)");
	exit(EXIT_FAILURE);
}

/**
 * check_file_status - Check status
 * @pathname: Name of path
 * @statbuf: Buffer
 * Return: True if file exists, false otherwise
*/

bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);
	if (stat_return == 0)
		return (true);
	return (false);
}

/**
 * handle_error - Will handle the error
 * @pid: Parent process id
 * Return: void
*/
void handle_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
}

/**
 * split_string - Will split string
 * @str: String input
 * substrings: strings
 * @count: Pointer of substrings count
 * @delimiter: character
 * Return: Array of substrings
*/
char **split_string(const char *str, const char *delimiter, int *count)
{
	char **substrings = NULL;
	int substrings_count = 0;
	char *str_copy = strdup(str);

	char *token = strtok(str_copy, delimiter);

	while (token != NULL)
	{
		substrings = realloc(substrings, sizeof(char *) * (substrings_count + 1));
		substrings[substrings_count] = strdup(token);
		substrings_count++;
		token = strtok(NULL, delimiter);
	}
	free(str_copy);
	*count = substrings_count;
	return (substrings);
}

/**
 * free_substrings - Will free memory allocated for substrings array.
 * @substrings: Strings array
 * @count: Number of substrings
 * this function frees memory allocated for each substrings
 * and then frees the memory for allocated array.
*/
void free_substrings(char **substrings, int count)
{
	for (int i = 0; i < count; i++)
	{
		free(substrings[i]);
	}
	free(substrings[i]);
}
