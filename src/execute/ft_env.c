/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:01:29 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/26 20:46:31 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd	*cmd)
{
	t_env	*env;

	if (cmd->content)
	{
		ft_putstr_fd(*cmd->content, 2);
		ft_putstr_fd(": No such file or diretoty\n", 2);
		g_info.last_exit_num = 127;
		return ;
	}
	env = g_info.env_lst;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	g_info.last_exit_num = 0;
}
