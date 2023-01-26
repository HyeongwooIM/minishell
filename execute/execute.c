/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:54:05 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/26 20:15:40 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	wait_child(int pipe_cnt)
// {
// 	int	i;
// 	int	status;

// 	i = -1;
// 	while (++i <= pipe_cnt)
// 		wait(&status);
// 	status = status >> 8;
// 	g_info.last_exit_num = status;
// }

void	single_command(t_cmd	*cmd)
{
	int	p_in;
	int	p_out;
	int	flag;

	flag = 0;
	p_in = dup(STDIN_FILENO);
	p_out = dup(STDOUT_FILENO);
	if (check_builtin(cmd->name) && !cmd->next)
	{
		single_builtin(cmd);
	}
	else if (cmd)
		ft_fork(0, cmd);
	else if (!cmd)
		ft_rdir(cmd->rdir);
	dup2(p_in, STDIN_FILENO);
	dup2(p_out, STDOUT_FILENO);
}

int	pipe_count(t_cmd	*cmd)
{
	int	count;

	count = -1;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

void	execute(t_cmd	*cmd)
{
	int		pipe_cnt;
	t_env	*env;

	if (!cmd)
		return ;
	pipe_cnt = pipe_count(cmd);
	if (check_heredoc(cmd))
		return ;
	if (cmd->next == 0)
		single_command(cmd);
	else
		ft_fork(pipe_cnt, cmd);
	return ;
}
