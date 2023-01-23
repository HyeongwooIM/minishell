/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:59:35 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/23 18:01:12 by woohyeong        ###   ########.fr       */
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
	return ;
}
