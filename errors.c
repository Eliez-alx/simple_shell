#include "shell.h"

/**
 * _eputs - this prints an input string
 * @str: the string to be printed
 * Return: 1
 */
int _eputs(char *str)
{
	int i = 0;

	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
	return (0);
}

/*
 * _eputchar - this writes the character c to stderr
 * @c: The character to be printed
 * Return: 1 on success
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - this writes the character c to a given fd
 * @c: The character to print
 * @fd: The file descriptor to be written
 * Return: On success return 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - used to print an input string
 * @str: the string to be printed
 * @fd: the file descriptor to be written
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
