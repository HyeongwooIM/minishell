#include "../minishell.h"

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
	int		heredoc_cnt;

	tmp = cmd;
	while (tmp) {
		check_rdir(tmp->rdir);
		tmp = tmp->next;
	}
	return ;
}

void	execute(t_cmd	*cmd)
{
	int	pipe_cnt;

	check_heredoc(cmd);
	if (cmd->next == 0 && check_builtin(cmd->name))
		single_builtin(cmd);
	else
		ft_exe(cmd);
	return ;
}