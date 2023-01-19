#include "../minishell.h"

char *here_doc_end_point(t_cmd *cmd)
{
	t_rdir *rdir;
	char	*end_point;
	
	rdir = cmd->rdir;
	while (rdir)
	{
		if (rdir->type == HEREDOC)
			break ;
		rdir = rdir->next;
	}
	if (!rdir)
		exit(1);
	end_point = ft_strdup(rdir->with);
	return (end_point);
}

void ft_here_doc(t_cmd *cmd)
{
	pid_t pid;
	int fd[2];
	char *buff;
	char *end_point;

	end_point = here_doc_end_point(cmd);
	if (!pipe(fd) || !end_point)
		exit(1);
	pid = fork();
	while (1)
	{
		buff = readline(">");
		if (!strcmp(buff, end_point))
			break ;
		while(buff++)
			write(fd[1], buff, 1);
		write(fd[1], "\n", 1);
	}
	return ;
}