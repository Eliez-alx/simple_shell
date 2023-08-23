#include <stdio.h>
#include "shell.h"
/**
* _strncmp - compares two strings up to n bytes
* @s1: compared to s2
* @s2: compared to s1
* @n: number of bytes
*
* Return: difference between s1 and s2
*/
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}
/**
 * _strlen -  returns the length of a string
 * @s:string
 * Return: length
 */
int _strlen(char *s)
{
	int longi = 0;

	while (*s != '\0')
	{
		longi++;
		s++;
	}
	return (longi);
}

/**
 * _strcmp - compares two strings
 * @s1: pointer to first string
 * @s2: pointer to second string
 * Return: if str1 < str2, negative difference is unmatched char
 * if str1 == str2, 0
 * if str1 > str2, positive difference is unmatched char
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/**
 *  *_strcat- concatenate two strings
 *  @dest: first string
 *  @src: second string
 *  Return: pointer
 */
char  *_strcat(char *dest, char *src)
{
	int r = 0;

	int s = 0;

	while (dest[r] != '\0')
	{
		r++;
	}
	while (src[s] != '\0')
	{
		dest[r] = src[s];
		r++;
		s++;
	}
	dest[r] = '\0';
	return (dest);
}
/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
*
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
