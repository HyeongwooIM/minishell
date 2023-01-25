//
// Created by jiyun on 2023/01/23.
//
#include "minishell.h"

void remove_delim(char *str, char delim) {
    int i;

    i = 0;
    while (str[i] != delim)
        ++i;
    while (str[i + 1])
    {
        str[i] = str[i + 1];
        i++;
    }
    str[i] = '\0';
}

char	get_delim(char *str)
{
	while (*str)
	{
		if (*str == '\"')
			return ('\"');
		if (*str == '\'')
			return ('\'');
		str++;
	}
	return (0);
}

char	*dequote(char *str)
{
	char	*ret;
	char	delim;

	delim = get_delim(str);
    remove_delim(str, delim);
    remove_delim(str, delim);
	ret = ft_strdup(str);
	free(str);
	if (*ret == '\0')
		return (0);
	return (ret);
}

char	*dequote_any(char *str, char delim)
{
	char	*ret;

	remove_delim(str, delim);
	remove_delim(str, delim);
	ret = ft_strdup(str);
	free(str);
	if (*ret == '\0')
		return (0);
	return (ret);
}