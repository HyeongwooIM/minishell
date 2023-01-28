/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:59:35 by him               #+#    #+#             */
/*   Updated: 2023/01/28 22:30:53 by woohyeong        ###   ########.fr       */
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
		while (*str)
		{
			if (check_n(*str) && n == 1)
				str++;
			else 
			{
				n++;
				ft_putstr_fd(*str, 1);
				str++;
				if (*str)
					write(1, " ", 1);
			}
		}
	}
	if (!n)
		write(1, "\n", 1);
	g_info.last_exit_num = 0;
}
