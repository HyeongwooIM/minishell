/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:56:48 by him               #+#    #+#             */
/*   Updated: 2023/01/29 16:39:08 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_content(char	*str)
{
	if (*str && (*str == '-' || *str == '+'))
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_cmd	*cmd)
{
	int				exit_num;
	char			**str;

	str = cmd->content;
	if (!str)
		exit (0);
	if (check_content(*(cmd->content)) != 1)
		ft_error_exit("exit : numeric argument required", 255);
	if (str[0] != 0 && str[1] != 0)
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_info.last_exit_num = 1;
		return ;
	}
	exit_num = ft_atoi(*(cmd->content));
	exit(exit_num);
}
