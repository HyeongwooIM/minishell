#include "minishell.h"

void ft_rdir(t_rdir *rdir)
{
	int in_fd;
	int out_fd;

	in_fd = 0;
	out_fd = 1;
	while (rdir)
	{
		if (rdir->type == RDIR || rdir->type == D_RDIR)  // > or >>
		{
			if (out_fd != 1)
				close(out_fd);
			if (rdir->type == RDIR)
				out_fd = open(rdir->with,O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (rdir->type == D_RDIR)
				out_fd = open(rdir->with,O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (rdir->type == R_RDIR || rdir->type == HEREDOC) // <
		{
			if (in_fd != 0)
				close(in_fd);
			if (rdir->type == R_RDIR)
				in_fd = open(rdir->with, O_RDONLY);
			if (rdir->type == HEREDOC && rdir->here_doc_fd)
				in_fd = rdir->here_doc_fd;
		}
		rdir = rdir->next;
	}
    if (in_fd != 0)
        dup2(in_fd, STDIN_FILENO);
    if (out_fd != 1)
        dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	close(in_fd);
	return ;
}
