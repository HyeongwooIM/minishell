/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:06:20 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/27 10:35:01 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void child_signal_handler(int signo)
// {
// 	if (signo)// == SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit: 3\n", 2);
// 		exit (255);
// 	}
// 	ft_putstr_fd("Quit: 3\n", 2);
// 	exit(199);
// }

static void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	wait_child(int pipe_cnt)
{
	int	i;
	int	status;

	i = -1;
	while (++i <= pipe_cnt)
		wait(&status);
	if (status == 2)
	{
		printf("\n");
		g_info.last_exit_num = status + 128;
	}
	else if (status == 3)
	{
		printf("Quit: %d\n", status);
		g_info.last_exit_num = status + 128;
	}
	else
		g_info.last_exit_num = status >> 8;
}

void	child_pro(int pipes[2][2], int pipe_cnt, int i, t_cmd *cmd)
{
	child_signal();
	close(pipes[0][0]);
	if (pipe_cnt && i != pipe_cnt)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close(pipes[0][1]);
	}
	if (i != 0)
	{
		dup2(pipes[1][0], STDIN_FILENO);
		close(pipes[1][0]);
	}
	if (cmd->rdir)
	{
		if (ft_rdir(cmd->rdir))
			exit (1);
	}
	if (check_builtin(cmd->name))
		is_builtin(cmd);
	else
		ft_exe(cmd, g_info.env_lst);
	exit(0);
}

void	connect_pipe(int pipe_cnt, int pipes[2][2], t_cmd *cmd)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i <= pipe_cnt)
	{
		if (pipe(pipes[0]) == -1)
			ft_error_exit("pipe error", 1);
		if (!pipe_cnt)
			close(pipes[0][1]);
		pid = fork();
		if (pid == -1)
			ft_error_exit("fork error", 1);
		if (pid == 0)
			child_pro(pipes, pipe_cnt, i, cmd);
		close(pipes[0][1]);
		if (i > 0)
			close(pipes[1][0]);
		pipes[1][0] = pipes[0][0];
		if (i == pipe_cnt)
			close((pipes[0][0]));
		cmd = cmd->next;
	}
	wait_child(pipe_cnt);
}

void	ft_fork(int pipe_cnt, t_cmd *cmd)
{
	int		pipes[2][2];

	ignore_signal();
	connect_pipe(pipe_cnt, pipes, cmd);
	return ;
}
