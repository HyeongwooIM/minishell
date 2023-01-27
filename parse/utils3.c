/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:10:56 by jiyun             #+#    #+#             */
/*   Updated: 2023/01/27 16:11:04 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

int	is_env(char c)
{
	if (c == '\0')
		return (0);
	if (is_space(c))
		return (0);
	if (c == '$')
		return (0);
	if (c == '\"')
		return (0);
	return (1);
}

char	*env_value(char *str)
{
	t_env	*env;
	char	*ret;

	env = find_env(str);
	if (!env)
		return (0);
	ret = ft_strdup(env->value);
	return (ret);
}

int	ft_isalnum_underbar(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_')
		return (1);
	if (('0' <= c && c <= '9'))
		return (1);
	return (0);
}
