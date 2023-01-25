/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:38:50 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/25 09:30:19 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		ft_error_exit("dup error", 1);
	close(fd1);
}

int	fd_out(int *out_fd, t_rdir *rdir)
{
	if (*out_fd != 1)
		close(*out_fd);
	if (rdir->type == RDIR)
		*out_fd = open(rdir->with, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdir->type == D_RDIR)
		*out_fd = open(rdir->with, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd == -1)
	{
		ft_putstr_fd("file open error\n", 2);
		return (1);
	}
	return (0);
}

int	fd_in(int *in_fd, t_rdir *rdir)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (rdir->type == R_RDIR)
		*in_fd = open(rdir->with, O_RDONLY);
	else if (rdir->type == HEREDOC && rdir->here_doc_fd)
		*in_fd = rdir->here_doc_fd;
	if (*in_fd == -1)
	{
		ft_putstr_fd("file open erro\nr", 2);
		return (1);
	}
	return (0);
}

int	ft_rdir(t_rdir *rdir)
{
	int	in_fd;
	int	out_fd;
	int	error_flag;

	in_fd = 0;
	out_fd = 1;
	while (rdir)
	{
		if (rdir->type == RDIR || rdir->type == D_RDIR)
			error_flag = fd_out(&out_fd, rdir);
		if (rdir->type == R_RDIR || rdir->type == HEREDOC)
			error_flag = fd_in(&in_fd, rdir);
		if (error_flag)
			break ;
		rdir = rdir->next;
	}
	if (in_fd > 2)
		dup_close(in_fd, STDIN_FILENO);
	if (out_fd > 2)
		dup_close(out_fd, STDOUT_FILENO);
	if (in_fd == -1 || out_fd == -1)
		return (1);
	return (0);
}
