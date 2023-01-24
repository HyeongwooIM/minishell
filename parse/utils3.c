//
// Created by jiyun on 2023/01/23.
//
#include "minishell.h"

char *dequote(char *str)
{
	char *ret;

	str[ft_strlen(str) - 1] = '\0';
	ret = ft_strdup(str + 1);
	free(str);
	if (*ret == '\0')
		return (0);
	return (ret);
}

char *dequote_h(char *str, int type)
{
	char	*ret;
	char	delim;
	int		i;

	if (type == S_QUOTE)
		delim = '\'';
	else
		delim = '\"';
	i = 0;
	while (str[i] != delim)
		++i;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
	i = 0;
	while (str[i] != delim)
		++i;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
	ret = ft_strdup(str);
	free(str);
	if (*ret == '\0')
		return (0);
	return (ret);
}