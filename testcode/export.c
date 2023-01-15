#include <stdio.h>
#include <unistd.h>
#include "../../minishell.h"

char **find_key_value(char *key_value)
{
	char **res;
	unsigned int len;

	res = malloc(sizeof(char *) * 3);
	if (!ft_strchr(key_value, '='))
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = ft_strdup(key_value);
		res[1] = 0;
		return (res);
	}
	res = malloc(sizeof(char *) * 3);
	len = ft_strchr(key_value, '=') - key_value;
	res[0] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(res[0], key_value, len + 1);
	res[1] = ft_strdup(key_value + len + 1);
	res[2] = 0;
	return (res);
}

int main()
{
	char **str;

	str = find_key_value("str123=123123123=123=123=");
	if (str)
		printf("key = %s\nvalue = %s", str[0], str[1]);
	else
		printf("key = %s\n", str[0]);
	return (0);
}