/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:48:52 by him               #+#    #+#             */
/*   Updated: 2023/01/26 21:48:53 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_exit(char *str, int error_no)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(error_no);
}

void	ft_command_error(char *cmd)
{
	if (cmd == 0 || *cmd == 0)
	{
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_info.last_exit_num = 127;
	exit(127);
}
