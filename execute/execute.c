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

void	execute(t_cmd	*cmd, t_env *env)
{
	int	pipe_cnt;

	if (!cmd)
		return ;
	pipe_cnt = check_pipe(cmd);
	check_heredoc(cmd);
	if (cmd->next == 0 && check_builtin(cmd->name))
		single_builtin(cmd, env);
	else
		ft_exe(cmd);
	if (pipe_cnt > 0)
	{
		while (pipe_cnt-- >= 0)
		{
		int pid;
		pid = fork();
		if (pid == 0)
		{
			redir(cmd);
			pipe();
			child_pro();
		}
		cmd = cmd->next;
		}
	}
	return ;
}