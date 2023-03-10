/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:06:08 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:58:43 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || \
			c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	just_white_space(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd) * 1);
	if (!ret)
		ft_error_exit("malloc error", 1);
	ret->name = NULL;
	ret->content = NULL;
	ret->rdir = NULL;
	ret->is_heredoc = 0;
	ret->next = NULL;
	return (ret);
}
