/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:02:18 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/26 20:47:08 by him              ###   ########.fr       */
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
	unsigned int	len;
	char			**str;

	str = cmd->content;
	len = 0;
	if (!str)
		exit (0);
	if (str[1] != 0 && str[2] != 0)
	{
		ft_putstr_fd("exit : too many arguments\n", 1);
		g_info.last_exit_num = 1;
		return ;
	}
	if (check_content(*(cmd->content)) != 1)
		ft_error_exit("exit : numeric argument required", 255);
	exit_num = ft_atoi(*(cmd->content));
	ft_putstr_fd("exit\n", 1);
	exit(exit_num);
}
