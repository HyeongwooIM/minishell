#include "../minishell.h

void	check_rdir(t_rdir *rdir)
{
	t_rdir *tmp;

	tmp = rdir;
	while (tmp)
	{
		tmp = tmp->next;
	}
}

void	check_heredoc(t_cmd	*cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp) {
		check_rdir(tmp->rdir);
		tmp = tmp->next;
	}
	return ;
}

void	execute(t_cmd	cmd)
{
	if(cmd)
	{
		//히어독 체크
		//히어
		check_heredoc(cmd);
	}
	return ;
}