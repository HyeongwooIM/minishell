#include "minishell.h"

void single_command(t_cmd *cmd)
{
	int	p_in;
	int	p_out;

	p_in = dup(STDIN_FILENO);
	p_out = dup(STDOUT_FILENO);
	if (!cmd->name)
		ft_rdir(cmd->rdir);
	else if(check_builtin(cmd->name))
		single_builtin(cmd);
	else
		ft_fork(0, cmd);
	dup2(p_in, STDIN_FILENO);
	dup2(p_out, STDOUT_FILENO);
}

int pipe_count(t_cmd *cmd)
{
	int count;

	count = -1;
	while (cmd)
	{
		cmd = cmd->next;
		count++;
	}
	return (count);
}

void execute(t_cmd *cmd)
{
	int	pipe_cnt;
	t_env *env;

	env = g_info.env_lst;
	pipe_cnt = pipe_count(cmd);
	check_heredoc(cmd);
	if (cmd->next == 0)
		single_command(cmd);
	else
		ft_fork(pipe_cnt, cmd);
	return ;
}