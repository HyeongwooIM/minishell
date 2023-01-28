/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:59:35 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:55:56 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char	*content)
{
	if (!content)
		return (0);
	if (*content == '-')
		content++;
	else
		return (0);
	while (*content == 'n')
		content++;
	if (*content == 0)
		return (1);
	return (0);
}

void	ft_echo(t_cmd	*cmd)
{
	int		n;
	char	**str;

	n = 0;
	str = cmd->content;
	if (str)
	{
		n = check_n(*str);
		if (n)
			str++;
		while (*str)
		{
			ft_putstr_fd(*str, 1);
			str++;
			if (*str)
				write(1, " ", 1);
		}
	}
	if (!n)
		write(1, "\n", 1);
	g_info.last_exit_num = 0;
}