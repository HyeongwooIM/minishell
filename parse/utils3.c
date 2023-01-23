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