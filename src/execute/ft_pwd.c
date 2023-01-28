/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:37:51 by him               #+#    #+#             */
/*   Updated: 2023/01/28 23:24:34 by woohyeong        ###   ########.fr       */
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
}
