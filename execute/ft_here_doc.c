/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:32:35 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/25 11:02:42 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_doc(int *fd, char *with)
{
	char	*buff;

	close(fd[0]);
	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		buff = readline("heredoc> ");
		if (ft_strcmp(buff, with) == 0)
		{
			write(fd[1], "\0", 1);
			break ;
		}
		write(fd[1], buff, ft_strlen(buff));
		write(fd[1], "\n", 1);
		free(buff);
	}
	free(buff);
	close(fd[1]);
	exit(0);
}

void	make_here_doc(t_rdir *rdir)
{
	pid_t	pid;
	int		fd[2];
	char	*buff;
	char	*temp;
	int		status;

	if (pipe(fd) == -1 || !rdir->with)
		ft_error_exit("create pipe faile", 1);
	ignore_signal();
	pid = fork();
	if (pid == -1)
		ft_error_exit("fork error", 1);
	if (pid == 0)
		read_doc(fd, rdir->with);
	close(fd[1]);
	wait(&status);
	status = status >> 8;
	g_info.last_exit_num = status;
	rdir->here_doc_fd = fd[0];
}

void	ft_heredoc(t_cmd *cmd)
{
	t_rdir	*tmp;

	tmp = cmd->rdir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			make_here_doc(tmp);
		tmp = tmp->next;
	}
}

void	check_heredoc(t_cmd *cmd)
{
	int	heredoc_cnt;

	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->is_heredoc)
			ft_heredoc(cmd);
		cmd = cmd->next;
	}
	return ;
}
