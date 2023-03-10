/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:37:51 by him               #+#    #+#             */
/*   Updated: 2023/01/29 16:29:32 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	get_cwd[PATH_MAX];

	if (!getcwd(get_cwd, PATH_MAX))
	{
		ft_putstr_fd("pwd error\n", 1);
		exit (1);
	}
	printf("%s\n", get_cwd);
	g_info.last_exit_num = 0;
}
