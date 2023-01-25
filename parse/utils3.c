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

char *dequote(char *str, int type)
{
	char	*ret;
	char	delim;

	if (type == D_QUOTE)
		delim = '\"';
	else
		delim = '\'';
    remove_delim(str, delim);
    remove_delim(str, delim);
	ret = ft_strdup(str);
	free(str);
	if (*ret == '\0')
		return (0);
	return (ret);
}
